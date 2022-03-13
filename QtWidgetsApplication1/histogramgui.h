#pragma once 
#include <qwidget.h>
#include "basketgui.h"
#include <qpainter.h>
class HistogramGUI :public QWidget,public Observer
{
	CosActivity& room;
public:
	HistogramGUI(CosActivity& room) :room{ room }
	{
		room.addObserver(this);
	}
	void paintEvent(QPaintEvent* ) override
	{
		QPainter p{ this };
		int var = 40;
		int i = 0;
		while(i<room.lista().size())
			//p.drawLine(0, 0, width(), height());
		{
			p.drawRect(80, 20, 40, var);
			var = var + 40;
			i++;
		}

		
	}
	void update() override
	{
		repaint();
	}
	~HistogramGUI()
	{
		room.removeObserver(this);
	}


};