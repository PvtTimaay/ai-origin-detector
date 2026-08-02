#pragma once

#include <string>
#include <vector>

namespace AiOriginDetector {

/// Supported media types that can be analysed.
enum class MediaType {
    Image,
    Audio,
    Voice,
    Text
};

/// Result returned by every detection function.
struct DetectionResult {
    MediaType   mediaType;
    double      confidenceScore; ///< 0.0 = human, 1.0 = fully AI-generated
    bool        isAiGenerated;
    std::string label;           ///< Human-readable verdict label
};

/// Core detector class. Instantiate once and reuse across multiple analyses.
class Detector {
public:
    Detector();
    ~Detector();

    /// Analyse an image file and return a detection result.
    DetectionResult analyseImage(const std::string& filePath);

    /// Analyse an audio file and return a detection result.
    DetectionResult analyseAudio(const std::string& filePath);

    /// Analyse a raw audio/voice buffer (PCM samples, 16-bit signed).
    DetectionResult analyseVoice(const std::vector<int16_t>& samples, int sampleRate);

    /// Analyse a plain-text string and return a detection result.
    DetectionResult analyseText(const std::string& text);

private:
    // Reserved for future model handles / internal state.
    struct Impl;
    Impl* pImpl;
};

} // namespace AiOriginDetector
