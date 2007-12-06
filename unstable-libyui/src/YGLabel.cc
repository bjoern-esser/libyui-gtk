/********************************************************************
 *           YaST2-GTK - http://en.opensuse.org/YaST2-GTK           *
 ********************************************************************/

#include <config.h>
#include <ycp/y2log.h>
#include <YGUI.h>
#include "YGUtils.h"
#include "YGWidget.h"

#include "YLabel.h"

class YGLabel : public YLabel, public YGWidget
{
public:
	YGLabel (YWidget *parent, const string &text, bool heading, bool outputField)
	: YLabel (NULL, text, heading, outputField),
	  YGWidget (this, parent, true, GTK_TYPE_LABEL, NULL)
	{
		IMPL
		gtk_misc_set_alignment (GTK_MISC (getWidget()), 0.0, 0.5);
		if (outputField)
			gtk_label_set_selectable (GTK_LABEL (getWidget()), TRUE);
		if (heading)
			YGUtils::setWidgetFont (getWidget(), PANGO_WEIGHT_ULTRABOLD, PANGO_SCALE_XX_LARGE);
		setLabel (text);
	}

	virtual void setText (const string &label)
	{
		gtk_label_set_label (GTK_LABEL (getWidget()), label.c_str());
		YLabel::setText (label);

		// Some YCP progs have no labeled labels cluttering the layout
		label.empty() ? gtk_widget_hide (getWidget()) : gtk_widget_show (getWidget());
	}

	YGWIDGET_IMPL_COMMON
	YGWIDGET_IMPL_USE_BOLD (YLabel)
};

YLabel *YGWidgetFactory::createLabel (YWidget *parent, const string &text, bool heading,
                                      bool outputField)
{
	return new YGLabel (parent, text, heading, outputField);
}
