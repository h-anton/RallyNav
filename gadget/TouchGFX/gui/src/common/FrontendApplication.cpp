#include <gui/common/FrontendApplication.hpp>
#include <osmscout/log/LoggerImpl.h>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{
    osmscout::log.Debug(true).Info(true).Warn(true).Error(true);
    osmscout::log.SetLogger(new osmscout::ConsoleLogger());

}
