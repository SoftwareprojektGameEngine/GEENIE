#include "viewerex.h"

ViewerEx::ViewerEx() : osgViewer::Viewer() {}
ViewerEx::ViewerEx(osg::ArgumentParser &parser) : osgViewer::Viewer(parser) {}
ViewerEx::ViewerEx(const ViewerEx &viewer, const osg::CopyOp &copyOp) : osgViewer::Viewer(viewer, copyOp) {}

void ViewerEx::setUpThreading() {
    Contexts contexts;
    getContexts(contexts);

    if (_threadingModel==SingleThreaded)
    {
        if (_threadsRunning) stopThreading();
        else
        {
            // we'll set processor affinity here to help single threaded apps
            // with multiple processor cores, and using the database pager.
            int numProcessors = OpenThreads::GetNumberOfProcessors();
            bool affinity = numProcessors>1;
            if (affinity)
            {
                // FIX: the following call caused OSG to crash
                // since it didn't do anything (even if it worked)
                // i commented it out.
                //OpenThreads::SetProcessorAffinityOfCurrentThread(0);

                Scenes scenes;
                getScenes(scenes);

                for(Scenes::iterator scitr = scenes.begin();
                    scitr != scenes.end();
                    ++scitr)
                {
                    if ((*scitr)->getSceneData())
                    {
                        // update the scene graph so that it has enough GL object buffer memory for the graphics contexts that will be using it.
                        (*scitr)->getSceneData()->resizeGLObjectBuffers(osg::DisplaySettings::instance()->getMaxNumberOfGraphicsContexts());
                    }
                }
            }
        }
    }
    else
    {
        if (!_threadsRunning) startThreading();
    }
}
