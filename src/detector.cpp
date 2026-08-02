#include "detector.h"

#include <stdexcept>
#include <string>

namespace AiOriginDetector {

// ---------------------------------------------------------------------------
// Internal implementation state (pImpl idiom)
// ---------------------------------------------------------------------------
struct Detector::Impl {
    // Future: model handles, configuration, caches, etc.
};

// ---------------------------------------------------------------------------
// Construction / Destruction
// ---------------------------------------------------------------------------
Detector::Detector() : pImpl(new Impl()) {}

Detector::~Detector() {
    delete pImpl;
}

// ---------------------------------------------------------------------------
// Helper – build a result from a raw confidence value
// ---------------------------------------------------------------------------
static DetectionResult makeResult(MediaType type, double confidence) {
    DetectionResult result;
    result.mediaType       = type;
    result.confidenceScore = confidence;
    result.isAiGenerated   = confidence >= 0.5;
    result.label           = result.isAiGenerated ? "AI-generated" : "Human-created";
    return result;
}

// ---------------------------------------------------------------------------
// Image analysis
// ---------------------------------------------------------------------------
DetectionResult Detector::analyseImage(const std::string& filePath) {
    if (filePath.empty()) {
        throw std::invalid_argument("analyseImage: filePath must not be empty");
    }

    // TODO: load image with OpenCV / stb_image and run detection model.
    double confidence = 0.0;
    return makeResult(MediaType::Image, confidence);
}

// ---------------------------------------------------------------------------
// Audio analysis
// ---------------------------------------------------------------------------
DetectionResult Detector::analyseAudio(const std::string& filePath) {
    if (filePath.empty()) {
        throw std::invalid_argument("analyseAudio: filePath must not be empty");
    }

    // TODO: decode audio file (libsndfile / dr_libs) and run detection model.
    double confidence = 0.0;
    return makeResult(MediaType::Audio, confidence);
}

// ---------------------------------------------------------------------------
// Voice analysis
// ---------------------------------------------------------------------------
DetectionResult Detector::analyseVoice(const std::vector<int16_t>& samples,
                                        int sampleRate) {
    if (samples.empty()) {
        throw std::invalid_argument("analyseVoice: samples must not be empty");
    }
    if (sampleRate <= 0) {
        throw std::invalid_argument("analyseVoice: sampleRate must be positive");
    }

    // TODO: run voice-synthesis detection on PCM samples.
    double confidence = 0.0;
    return makeResult(MediaType::Voice, confidence);
}

// ---------------------------------------------------------------------------
// Text analysis
// ---------------------------------------------------------------------------
DetectionResult Detector::analyseText(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("analyseText: text must not be empty");
    }

    // TODO: run LLM-origin classifier on the input text.
    double confidence = 0.0;
    return makeResult(MediaType::Text, confidence);
}

} // namespace AiOriginDetector
