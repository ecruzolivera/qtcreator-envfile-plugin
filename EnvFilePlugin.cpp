#include "EnvFilePlugin.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectmanager.h>
#include <projectexplorer/target.h>

#include <QDebug>

#include "EnvFileSettings.h"

using namespace ProjectExplorer;
using namespace Utils;

namespace EnvFilePlugin::Internal {

const QString EnvFilePluginPlugin::ENV_FILE_PATTERN = ".env";

EnvFilePluginPlugin::EnvFilePluginPlugin()
{
    // Create your members
}

EnvFilePluginPlugin::~EnvFilePluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool EnvFilePluginPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    // If you need access to command line arguments or to report errors, use the
    //    bool IPlugin::initialize(const QStringList &arguments, QString *errorString)
    // overload.
    auto isEnable = EnvFile::settings().enableLoadEnvFile();
    if (isEnable) {
      processEnvFile();
    }

    return true;
}

void EnvFilePluginPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag EnvFilePluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void EnvFilePluginPlugin::processEnvFile() {
  const auto envFilePath = EnvFile::settings().envFilePath().path();
  const auto isEnabled = EnvFile::settings().enableLoadEnvFile();
  qInfo() << "envFilePath  " << envFilePath;
  qInfo() << "isEnabled   " << isEnabled;
  if (!isEnabled) {
    return;
  }
  connect(ProjectManager::instance(), &ProjectManager::projectAdded, this, connectProject);
}

void EnvFilePluginPlugin::connectProject(ProjectExplorer::Project *project) {
  qDebug() << "project " << project->displayName();
  connect(project, &Project::addedTarget, project, [project](Target *target) { processTarget(project, target); });
  connect(project, &Project::activeTargetChanged, project, [project](Target *target) {
    processTarget(project, target);
  });
  auto activeTarget = project->activeTarget();
  processTarget(project, activeTarget);
}

void EnvFilePluginPlugin::processTarget(ProjectExplorer::Project *project, ProjectExplorer::Target *target) {
  if (!project) {
    qDebug() << "no project";
    return;
  }

  if (!target) {
    qDebug() << "no target";
    return;
  }
  qDebug() << "project " << project->displayName();
  qDebug() << "target " << target->displayName();

  const auto projectDirectory = project->projectDirectory();

  qDebug() << "projectDirectory  " << projectDirectory;

  const auto projectEnvFilePath = projectDirectory / ENV_FILE_PATTERN;
  qDebug() << "envFilePath  " << projectEnvFilePath;
}

}  // namespace EnvFilePlugin::Internal