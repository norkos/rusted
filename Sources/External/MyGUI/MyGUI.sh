if [ ! -f "$artefacts" ]; then
    mkdir -p $mygui_dir
    cd $mygui_dir
    echo $OGRE_ogredeps_dir
    cmake $mygui_src $__configuration_cmake_flags -DMYGUI_STATIC=1 -DMYGUI_RENDERSYSTEM=2 -DOGRE_SOURCE=$OGRE_ogre_src -DOGRE_BUILD=$OGRE_ogre_dir -DMYGUI_DEPENDENCIES_DIR=$OGRE_ogredeps_dir/ogredeps
    make MyGUIEngine MyGUI.OgrePlatform
    cp -v $mygui_dir/lib/* $__build
fi

