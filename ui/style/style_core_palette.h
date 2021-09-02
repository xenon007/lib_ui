// This file is part of Desktop App Toolkit,
// a set of libraries for developing nice desktop applications.
//
// For license and copyright information please follow this link:
// https://github.com/desktop-app/legal/blob/master/LEGAL
//
#pragma once

#include "ui/style/style_core.h"
#include "styles/palette.h"

namespace style {

struct colorizer;

class palette : public palette_data {
public:
	palette() = default;
	palette(const palette &other) = delete;
	palette &operator=(const palette &other);
	~palette() {
		clear();
	}

	QByteArray save() const;
	bool load(const QByteArray &cache);

	enum class SetResult {
		Ok,
		KeyNotFound,
		ValueNotFound,
		Duplicate,
	};
	SetResult setColor(QLatin1String name, uchar r, uchar g, uchar b, uchar a);
	SetResult setColor(QLatin1String name, QLatin1String from);
	void reset();

	// Created not inited, should be finalized before usage.
	void finalize(const colorizer &with);
	void finalize();

	int indexOfColor(color c) const;
	color colorAtIndex(int index) const;

private:
	struct TempColorData { uchar r, g, b, a; };
	friend class palette_data;

	void clear();
	void compute(int index, int fallbackIndex, TempColorData value);
	void setData(int index, const internal::ColorData &value);

	const colorizer *_colorizer = nullptr;
	bool _ready = false;

};

namespace main_palette {

not_null<const palette*> get();
QByteArray save();
bool load(const QByteArray &cache);
palette::SetResult setColor(QLatin1String name, uchar r, uchar g, uchar b, uchar a);
palette::SetResult setColor(QLatin1String name, QLatin1String from);
void apply(const palette &other);
void reset();
int indexOfColor(color c);

} // namespace main_palette
} // namespace style
