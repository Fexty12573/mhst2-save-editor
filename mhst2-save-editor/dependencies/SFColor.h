#pragma once

#include <SFML/Graphics.hpp>


namespace sf
{
	struct HSVColor
	{
		Uint8 h, s, v;
		
    public:
        HSVColor(Uint8 h, Uint8 s, Uint8 v)
            : h(h), s(s), v(v)
        {}
        HSVColor()
            : h(0), s(0), v(0)
        {}

		Color as_rbga() const
		{
            Color rgb;
            unsigned char region, remainder, p, q, t;

            if (s == 0)
            {
                rgb.r = v;
                rgb.g = v;
                rgb.b = v;
                return rgb;
            }

            region = h / 43;
            remainder = (h - (region * 43)) * 6;

            p = (v * (255 - s)) >> 8;
            q = (v * (255 - ((s * remainder) >> 8))) >> 8;
            t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

            switch (region)
            {
            case 0:
                rgb.r = v; rgb.g = t; rgb.b = p;
                break;
            case 1:
                rgb.r = q; rgb.g = v; rgb.b = p;
                break;
            case 2:
                rgb.r = p; rgb.g = v; rgb.b = t;
                break;
            case 3:
                rgb.r = p; rgb.g = q; rgb.b = v;
                break;
            case 4:
                rgb.r = t; rgb.g = p; rgb.b = v;
                break;
            default:
                rgb.r = v; rgb.g = p; rgb.b = q;
                break;
            }

            return rgb;
        }
	};

	class ColorPlus
	{
	private:
		Color _rgb;
        HSVColor _hsv;

	public:
        ColorPlus(const Color& c)
            : _rgb(c)
        {
            update_hsv();
        }
        ColorPlus(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
            : _rgb(r, g, b, a)
        {
            update_hsv();
        }
        ColorPlus(const HSVColor& c)
            : _rgb(c.as_rbga()), _hsv(c)
        {}
        ColorPlus()
            : _rgb(Color()), _hsv(HSVColor())
        {}

    public:
        const Color& rgba() const { return _rgb; };
        const HSVColor& hsv() const { return _hsv; }

        const Uint8& r() const { return _rgb.r; }
        const Uint8& g() const { return _rgb.g; }
        const Uint8& b() const { return _rgb.b; }
        const Uint8& a() const { return _rgb.a; }
        void r(Uint8 r) { _rgb.r = r; update_hsv(); }
        void g(Uint8 g) { _rgb.g = g; update_hsv(); }
        void b(Uint8 b) { _rgb.b = b; update_hsv(); }
        void a(Uint8 a) { _rgb.a = a; update_hsv(); }

        const Uint8& h() const { return _hsv.h; }
        const Uint8& s() const { return _hsv.s; }
        const Uint8& v() const { return _hsv.v; }
        void h(Uint8 h) { _hsv.h = h; update_rgb(); }
        void s(Uint8 s) { _hsv.s = s; update_rgb(); }
        void v(Uint8 v) { _hsv.v = v; update_rgb(); }

    private:
        void update_hsv()
        {
            unsigned char rgbMin, rgbMax;

            rgbMin = _rgb.r < _rgb.g ? (_rgb.r < _rgb.b ? _rgb.r : _rgb.b) : (_rgb.g < _rgb.b ? _rgb.g : _rgb.b);
            rgbMax = _rgb.r > _rgb.g ? (_rgb.r > _rgb.b ? _rgb.r : _rgb.b) : (_rgb.g > _rgb.b ? _rgb.g : _rgb.b);

            _hsv.v = rgbMax;
            if (_hsv.v == 0)
            {
                _hsv.h = 0;
                _hsv.s = 0;
            }

            _hsv.s = 255 * long(rgbMax - rgbMin) / _hsv.v;
            if (_hsv.s == 0)
            {
                _hsv.h = 0;
            }

            if (rgbMax == _rgb.r)
                _hsv.h = 0 + 43 * (_rgb.g - _rgb.b) / (rgbMax - rgbMin);
            else if (rgbMax == _rgb.g)
                _hsv.h = 85 + 43 * (_rgb.b - _rgb.r) / (rgbMax - rgbMin);
            else
                _hsv.h = 171 + 43 * (_rgb.r - _rgb.g) / (rgbMax - rgbMin);
        }
        void update_rgb()
        {
            unsigned char region, remainder, p, q, t;

            if (_hsv.s == 0)
            {
                _rgb.r = _hsv.v;
                _rgb.g = _hsv.v;
                _rgb.b = _hsv.v;
            }

            region = _hsv.h / 43;
            remainder = (_hsv.h - (region * 43)) * 6;

            p = (_hsv.v * (255 - _hsv.s)) >> 8;
            q = (_hsv.v * (255 - ((_hsv.s * remainder) >> 8))) >> 8;
            t = (_hsv.v * (255 - ((_hsv.s * (255 - remainder)) >> 8))) >> 8;

            switch (region)
            {
            case 0:
                _rgb.r = _hsv.v; _rgb.g = t; _rgb.b = p;
                break;
            case 1:
                _rgb.r = q; _rgb.g = _hsv.v; _rgb.b = p;
                break;
            case 2:
                _rgb.r = p; _rgb.g = _hsv.v; _rgb.b = t;
                break;
            case 3:
                _rgb.r = p; _rgb.g = q; _rgb.b = _hsv.v;
                break;
            case 4:
                _rgb.r = t; _rgb.g = p; _rgb.b = _hsv.v;
                break;
            default:
                _rgb.r = _hsv.v; _rgb.g = p; _rgb.b = q;
                break;
            }
        }
	};
}

