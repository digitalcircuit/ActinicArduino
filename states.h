#ifndef __INC_AA_STATES
#define __INC_AA_STATES

/**
 * System state types
 */
namespace States
{
    /// System state
    enum class State {
        Idle,              ///< Powered on, no commands
        Linked,            ///< Computer has sent commands
        DisplayBlack,      ///< Set all lights off
        DisplayIdentify,   ///< Set lights to identify pattern
        DisplayDarkOrange, ///< Filled lights with dark orange
        DisplayOrange,     ///< Filled lights with bright orange
        DisplayAmbient,    ///< Filled lights with ambient/normal light color
        DisplayWhite,      ///< Filled lights with maximum color
    };
}
#endif
