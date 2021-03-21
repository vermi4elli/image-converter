#pragma once

enum class imageType
{
	PPM,
	BPM,
	GIF,
	PNG,
	JPEG,
	UNKNOWN
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

std::string printImageType(imageType value) {
	std::string temp;
	switch (value)
	{
	case imageType::PPM:
		temp = "ppm";
		break;
	case imageType::BPM:
		temp = "bpm";
		break;
	case imageType::GIF:
		temp = "gif";
		break;
	case imageType::PNG:
		temp = "png";
		break;
	case imageType::JPEG:
		temp = "jpeg";
		break;
	case imageType::UNKNOWN:
		temp = "unknown type";
		break;
	default:
		break;
	};

	return temp;
};