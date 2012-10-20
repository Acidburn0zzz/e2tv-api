#include "source.h"

QString Source::kindToStr(Source::Kind k)
{
	if (k == LIVE_TV)
		return "TV";
	if (k == PAY)
		return "Pay";
	if (k == STREAM)
		return "Streaming";
	if (k == TORRENT)
		return "Torrent";
	if (k == DVD_RENT)
		return "Rental";
	if (k == TRAILER)
		return "Trailer";
	return "";
}

Source::Source()
{
}
