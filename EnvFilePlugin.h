#pragma once

#include <extensionsystem/iplugin.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectmanager.h>

#include <optional>

namespace EnvFilePlugin::Internal {

class EnvFilePluginPlugin : public ExtensionSystem::IPlugin {
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
  static std::optional<QPair<QString, QString>> getEnvVarFromLine(const QString &line);
  static void loadEnvVariable(ProjectExplorer::Target *target, const QPair<QString, QString> &envVariable);
  static const QString ENV_FILE_PATTERN;
};

}  // namespace EnvFilePlugin::Internal
