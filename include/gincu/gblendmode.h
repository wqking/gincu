#ifndef GBLENDMODE_H
#define GBLENDMODE_H

// code in this file is mostly a rewritten from SFML

namespace gincu {

enum class GBlendFunc
{
	zero,
	one,
	sourceColor,
	oneMinusSourceColor,
	destColor,
	oneMinusDestColor,
	sourceAlpha,
	oneMinusSourceAlpha,
	destAlpha,
	oneMinusDestAlpha
};

enum class GBlendEquation
{
	add,
	subtract,
	reverseSubtract
};

struct GBlendModeChannel
{
	constexpr GBlendModeChannel()
		: source(), dest(), func()
	{}

	constexpr GBlendModeChannel(
		const GBlendFunc source,
		const GBlendFunc dest,
		const GBlendEquation func = GBlendEquation::add
	)
		: source(source), dest(dest), func(func)
	{}

	GBlendFunc source;
	GBlendFunc dest;
	GBlendEquation func;
};

inline bool operator == (const GBlendModeChannel & a, const GBlendModeChannel & b)
{
	return a.source == b.source && a.dest == b.dest && a.func == b.func;
}

struct GBlendMode
{
	constexpr GBlendMode()
		: colorChannel{ GBlendFunc::sourceAlpha, GBlendFunc::oneMinusSourceAlpha },
			alphaChannel{ GBlendFunc::one, GBlendFunc::oneMinusSourceAlpha }
	{}

	constexpr GBlendMode(
		const GBlendFunc source,
		const GBlendFunc dest,
		const GBlendEquation func = GBlendEquation::add
	)
		: colorChannel(source, dest, func), alphaChannel(source, dest, func)
	{}

	constexpr GBlendMode(
		const GBlendModeChannel colorChannel,
		const GBlendModeChannel alpha
	)
		: colorChannel(colorChannel), alphaChannel(alpha)
	{}

	GBlendModeChannel colorChannel;
	GBlendModeChannel alphaChannel;
};

inline bool operator == (const GBlendMode & a, const GBlendMode & b)
{
	return a.colorChannel == b.colorChannel && a.alphaChannel == b.alphaChannel;
}

inline bool operator != (const GBlendMode & a, const GBlendMode & b)
{
	return ! operator == (a, b);
}

constexpr GBlendMode blendModeDefault = GBlendMode();

constexpr GBlendMode blendModeAlpha(
	{ GBlendFunc::sourceAlpha, GBlendFunc::oneMinusSourceAlpha },
	{ GBlendFunc::one, GBlendFunc::oneMinusSourceAlpha });

constexpr GBlendMode blendModeAdd(
	{ GBlendFunc::sourceAlpha, GBlendFunc::one },
	{ GBlendFunc::one, GBlendFunc::one });

constexpr GBlendMode blendModeMultiply(GBlendFunc::destColor, GBlendFunc::zero);

constexpr GBlendMode blendModeNone(GBlendFunc::one, GBlendFunc::zero);


} //namespace gincu



#endif
