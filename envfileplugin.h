#pragma once

#include <extensionsystem/iplugin.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectmanager.h>

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
 static void connectTarget(ProjectExplorer::Project *project, ProjectExplorer::Target *target);
 void processEnvFile();
};

} // namespace EnvFilePlugin::Internal
