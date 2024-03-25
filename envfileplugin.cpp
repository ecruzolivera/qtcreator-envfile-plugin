#include "envfileplugin.h"

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
  auto envFilePath = EnvFile::settings().envFilePath().path();
  using namespace ProjectExplorer;

  qDebug() << "hereee1 ";
  // clang-format off
  connect(ProjectManager::instance(), &ProjectManager::projectAdded, this, [](Project *project) {

  qDebug() << "hereee2 ";
        connect(project, &Project::addedTarget, project, [project](Target *target) {

  qDebug() << "hereee3 ";
            connectTarget(project, target);
      });
  });
  // clang-format on
}

void EnvFilePluginPlugin::connectTarget(ProjectExplorer::Project *project, ProjectExplorer::Target *target) {
  qDebug() << "hereee5 ";
  // const auto projectDirectory = project->projectDirectory();
  qDebug() << "project " << project->displayName();
  qDebug() << "target " << target->displayName();
}

} // namespace EnvFilePlugin::Internal
