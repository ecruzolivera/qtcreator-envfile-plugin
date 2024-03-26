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
 void processEnvFile();
 static void connectProject(ProjectExplorer::Project *project);
 static void processTarget(ProjectExplorer::Project *project, ProjectExplorer::Target *target);
 static const QString ENV_FILE_PATTERN;
};

} // namespace EnvFilePlugin::Internal
