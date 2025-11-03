TMP=$(mktemp)
(cd builddir && meson introspect --install-plan) >$TMP

jq -r '.targets | keys[]' $TMP | while read -r KEY; do
    OUT=$(jq -r ".targets[\"$KEY\"].destination" $TMP)
    OUT=$(echo $OUT | sed -e "s|{libdir}|$BUILD/lib|g" -e "s|{libdir_shared}|$DEPLOY/lib|g")

    echo "Installing $OUT..."
    mkdir -p $(dirname $OUT)
    cp -u $KEY $OUT
done

rm -f $TMP