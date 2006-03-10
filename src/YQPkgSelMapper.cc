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

  File:	      YQPkgSelMapper.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#define y2log_component "qt-pkg"
#include <ycp/y2log.h>

#include "YQPkgSelMapper.h"


ZyppSel
findZyppSel( ZyppPkg pkg )
{
    YQPkgSelMapper mapper; // This will build a cache, if there is none yet
    ZyppSel sel;

    YQPkgSelMapper::CacheIterator it = YQPkgSelMapper::_cache.find( pkg );

    if ( it != YQPkgSelMapper::_cache.end() )
	sel = it->second;
    else
	y2warning( "No selectable found for package %s", pkg->name().c_str() );

    return sel;
}


int			YQPkgSelMapper::_refCount = 0;
YQPkgSelMapper::Cache	YQPkgSelMapper::_cache;


YQPkgSelMapper::YQPkgSelMapper()
{
    if ( ++_refCount == 1 )
	rebuildCache();
}



YQPkgSelMapper::~YQPkgSelMapper()
{
    if ( --_refCount == 0 )
    {
	y2debug( "Destroying pkg -> selectable cache" );
	_cache.clear();
    }
}


void YQPkgSelMapper::rebuildCache()
{
    _cache.clear();
    y2debug( "Building pkg -> selectable cache" );

    for ( ZyppPoolIterator sel_it = zyppPkgBegin();
	  sel_it != zyppPkgEnd();
	  ++sel_it )
    {
	ZyppSel sel = *sel_it;
	zypp::ui::Selectable::available_iterator it = sel->availableBegin();

	while ( it != sel->availableEnd() )
	{
	    ZyppPkg pkg = tryCastToZyppPkg( *it );

	    if ( pkg )
		_cache.insert( CachePair( pkg, sel ) );

	    ++it;
	}
    }

    y2debug( "Building pkg -> selectable cache done" );
}
