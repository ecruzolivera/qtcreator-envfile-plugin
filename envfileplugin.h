#pragma once


#include <extensionsystem/iplugin.h>

namespace EnvFilePlugin::Internal {

class EnvFilePluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "EnvFilePlugin.json")

public:
    EnvFilePluginPlugin();
    ~EnvFilePluginPlugin() override;

    bool initialize(const QStringList &arguments, QString *errorString) override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

private:
    void triggerAction();
};

} // namespace EnvFilePlugin::Internal
