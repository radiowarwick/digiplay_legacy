#ifndef COMPONENTMONITOR_H_
#define COMPONENTMONITOR_H_

#include <vector>
using std::vector;

#include "Audio.h"
#include "Component.h"

/** Monitor Component base class.
 * This provides a base for all audio components and implements functionality
 * such as interconnection of components and message passing.
 */
class Audio::ComponentMonitor : public virtual Audio::Component {
    public:
        /// Clean up all component mappings
        virtual ~ComponentMonitor();

    protected:
        /// Only derived classes from component can be created
        ComponentMonitor();

};
#endif /*COMPONENTMONITOR_H_*/
