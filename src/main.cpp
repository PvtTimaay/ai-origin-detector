#include "detector.h"

#include <iostream>
#include <string>

static void printResult(const AiOriginDetector::DetectionResult& result) {
    std::cout << "  Label      : " << result.label << "\n"
              << "  AI-origin  : " << (result.isAiGenerated ? "yes" : "no") << "\n"
              << "  Confidence : " << result.confidenceScore << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ai-origin-detector <type> <path|text>\n"
                  << "  type: image | audio | voice | text\n"
                  << "  path: path to the media file (image/audio/voice)\n"
                  << "  text: the text string to analyse\n";
        return 1;
    }

    const std::string mediaType = argv[1];
    const std::string input     = argv[2];

    AiOriginDetector::Detector detector;

    try {
        AiOriginDetector::DetectionResult result;

        if (mediaType == "image") {
            result = detector.analyseImage(input);
        } else if (mediaType == "audio") {
            result = detector.analyseAudio(input);
        } else if (mediaType == "voice") {
            result = detector.analyseAudio(input); // voice file path
        } else if (mediaType == "text") {
            result = detector.analyseText(input);
        } else {
            std::cerr << "Unknown media type: " << mediaType << "\n";
            return 1;
        }

        std::cout << "Detection result for [" << mediaType << "] \"" << input << "\":\n";
        printResult(result);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}
