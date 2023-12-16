// ColorUtility.cpp
#include "ColorUtility.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"

using namespace ci;

Color ColorUtility::generateColor() {
    // Implementation of generateColor
    return Color(Rand::randFloat(), Rand::randFloat(), Rand::randFloat());
}

Color ColorUtility::calculateAnalogousColor(const ci::Color& baseColor, float angleSeparation, float saturationBoost) {
    Color baseColorHSV = rgbToHsv(baseColor, saturationBoost);

    // Calculate the new hue based on the angular separation
    float newHue = fmod(baseColorHSV.r * 360.0f + angleSeparation, 360.0f) / 360.0f;

    // Use the new hue and maintain the modified saturation and brightness
    return Color(CM_HSV, newHue, baseColorHSV.g, baseColorHSV.b);
}

Color ColorUtility::rgbToHsv(const ci::Color& rgbColor, float saturationBoost) {
    // Implementation of rgbToHsv
    float r = rgbColor.r;
    float g = rgbColor.g;
    float b = rgbColor.b;

    float maxColor = math<float>::max(r, math<float>::max(g, b));
    float minColor = math<float>::min(r, math<float>::min(g, b));

    float hue, saturation, brightness;
    float delta = maxColor - minColor;

    brightness = maxColor;

    if (maxColor > 0) {
        saturation = delta / maxColor;

        // Apply saturation boost
        saturation += saturationBoost;
        saturation = math<float>::clamp(saturation, 0.0f, 1.0f);

        if (r == maxColor) {
            hue = (g - b) / delta;
        }
        else if (g == maxColor) {
            hue = 2 + (b - r) / delta;
        }
        else {
            hue = 4 + (r - g) / delta;
        }

        hue *= 60;
        if (hue < 0) {
            hue += 360;
        }
    }
    else {
        // r = g = b = 0
        // No saturation and hue is undefined
        saturation = 0;
        hue = 0;
    }

    return Color(hue / 360.0f, saturation, brightness);
}

Color ColorUtility::smoothColor(int iterationCount, float fractionalPart, double animationTime) {
    float t = static_cast<float>(iterationCount) + fractionalPart;
    float hue = fmod(t * 2.0f + animationTime, 1.0f);  // Adjust the frequency (0.1f) as needed
    return Color(CM_HSV, hue, 0.6f, 0.8f);  // Adjust saturation and brightness for a softer look
}