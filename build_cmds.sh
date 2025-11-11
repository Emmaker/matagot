# utility commands for when your making modifications/building;
# `cd` into the directory containing this script and source it.
#
# Adds the following commands to your shell:
#   mbuild - build Matagot
#   mclean - clean Matagot build fragments
#   mclean_bin - clean Matagot bin/ build fragments
#   mclean_lib - clean Matagot lib/ build fragments
#   mclean_hdr - clean Matagot include/ build fragments (kernel headers)

if [ ! -f "$PWD/build_cmds.sh" ]; then
	echo "cd into the directory containing build_cmds.sh before sourcing it!"
else
	MATAGOT=$PWD

	mbuild() { (cd $MATAGOT && bmake) }
	mclean() { (cd $MATAGOT && git clean -fX) }
	mclean_bin() { (cd $MATAGOT/bin && git clean -fX) }
	mclean_lib() { (cd $MATAGOT/lib && git clean -fX) }
	mclean_hdr() { (cd $MATAGOT/include && git clean -fX) }
fi
