#ifndef CLASS_COMPONENT_AUDIO
#define CLASS_COMPONENT_AUDIO

#include <vector>
using std::vector;

#include "Audio.h"
#include "Component.h"
#include "AudioPacket.h"

/** Audio Component base class.
 * This provides a base for all audio components and implements functionality
 * such as interconnection of components and message passing.
 */
class Audio::ComponentAudio : public virtual Audio::Component {
    public:
        /// Clean up all component mappings
        virtual ~ComponentAudio();
        /// Places \c samples stereo samples of audio into \c audioData.
        virtual void getAudio(AudioPacket* audioData __attribute__((unused)) ) {}

    protected:
        /// Only derived classes from component can be created
        ComponentAudio();

};
#endif
