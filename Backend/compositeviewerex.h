#ifndef COMPOSITEVIEWEREX_H
#define COMPOSITEVIEWEREX_H

#include <osgViewer\CompositeViewer>

class CompositeViewerEx : public osgViewer::CompositeViewer {
public:
	virtual void setUpThreading();
};

#endif
