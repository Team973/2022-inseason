#pragma once

#include <hal/Types.h>
#include <units/math.h>
#include <units/time.h>
#include <wpi/deprecated.h>
#include <wpi/priority_queue.h>

#include <functional>
#include <utility>
#include <vector>

#include "frc/IterativeRobotBase.h"
#include "frc/Timer.h"

namespace frc973 {
class Greybot : public frc::IterativeRobotBase {
public:
    static constexpr auto kDefaultPeriod = 20_ms;

    /**
     * Provide an alternate "main loop" via StartCompetition().
     */
    void StartCompetition() override;

    /**
     * Ends the main loop in StartCompetition().
     */
    void EndCompetition() override;

    /**
     * Constructor for Greybot.
     *
     * @deprecated use unit safe constructor instead.
     * Greybot(units::second_t period = kDefaultPeriod)
     *
     * @param period Period in seconds.
     */
    WPI_DEPRECATED("Use constructor with unit-safety instead.")
    explicit Greybot(double period);

    /**
     * Constructor for Greybot.
     *
     * @param period Period.
     */
    explicit Greybot(units::second_t period = kDefaultPeriod);

    ~Greybot() override;

    Greybot(Greybot&&) = default;
    Greybot& operator=(Greybot&&) = default;

    /**
     * Add a callback to run at a specific period with a starting time offset.
     *
     * This is scheduled on Greybot's Notifier, so Greybot and the callback
     * run synchronously. Interactions between them are thread-safe.
     *
     * @param callback The callback to run.
     * @param period   The period at which to run the callback.
     * @param offset   The offset from the common starting time. This is useful
     *                 for scheduling a callback in a different timeslot relative
     *                 to Greybot.
     */
    void AddPeriodic(std::function<void()> callback, units::second_t period, units::second_t offset = 0_s);

private:
    class Callback {
    public:
        std::function<void()> func;
        units::second_t period;
        units::second_t expirationTime;

        /**
         * Construct a callback container.
         *
         * @param func      The callback to run.
         * @param startTime The common starting point for all callback scheduling.
         * @param period    The period at which to run the callback.
         * @param offset    The offset from the common starting time.
         */
        Callback(std::function<void()> func, units::second_t startTime, units::second_t period, units::second_t offset)
                : func{std::move(func)}
                , period{period}
                , expirationTime{startTime + offset +
                                 units::math::floor((frc::Timer::GetFPGATimestamp() - startTime) / period) * period +
                                 period} {
        }

        bool operator>(const Callback& rhs) const {
            return expirationTime > rhs.expirationTime;
        }
    };

    hal::Handle<HAL_NotifierHandle> m_notifier;
    units::second_t m_startTime;

    wpi::priority_queue<Callback, std::vector<Callback>, std::greater<Callback>> m_callbacks;
};
}  // namespace frc973