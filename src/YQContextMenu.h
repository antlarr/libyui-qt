/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YQContextMenu.h

  Author:     Thomas Goettlicher <tgoettlicher@suse.de>

/-*/


#ifndef YQContextMenu_h
#define YQContextMenu_h

#include <qwidget.h>
#include "YContextMenu.h"
#include <QHash>

class QAction;
class QPushButton;
class QMenu;

class YQContextMenu : public QObject,  public YContextMenu
{
    Q_OBJECT

public:
    /**
     * Constructor.
     **/
//    YQContextMenu( YWidget * 		parent,
//		  const string &	label );
    YQContextMenu( );
    YQContextMenu( const QPoint position );


    /**
     * Destructor.
     **/
    virtual ~YQContextMenu();

    /**
     * Change the label on the button.
     *
     * Reimplemented from YContextMenu / YSelectionWidget.
     **/
//    virtual void setLabel( const string & label );

    /**
     * Rebuild the displayed menu tree from the internally stored YMenuItems.
     *
     * Implemented from YContextMenu.
     **/
    virtual void rebuildMenuTree();
    
    /**
     * Set enabled / disabled state.
     *
     * Reimplemented from YWidget.
     **/
//    virtual void setEnabled( bool enabled );

    /**
     * Preferred width of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredWidth();

    /**
     * Preferred height of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredHeight();

    /**
     * Set the new size of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setSize( int newWidth, int newHeight );
    
    /**
     * Accept the keyboard focus.
     **/
//    virtual bool setKeyboardFocus();

    
protected slots:

    /**
     * Triggered when any menu item is activated.
     **/
    void menuEntryActivated( QAction * menuItem );

    /**
     * Triggered via menuEntryActivated() by zero timer to get back in sync
     * with the Qt event loop. 
     **/
    void returnNow();

    
protected:

    /**
     * Recursively insert menu items into 'menu' from iterator 'begin' to iterator 'end'.
     **/
    void rebuildMenuTree( QMenu * menu, YItemIterator begin, YItemIterator end );

    
    //
    // Data members
    //
    
    YMenuItem *		_selectedItem;
    QPushButton * 	_qt_button;
    QHash<QAction*,int> _serials;


private:
    QPoint 		_position;

};

#endif // YQContextMenu_h