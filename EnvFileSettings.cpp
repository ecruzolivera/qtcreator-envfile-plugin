#include "EnvFileSettings.h"

#include <coreplugin/dialogs/ioptionspage.h>
#include <utils/hostosinfo.h>
#include <utils/layoutbuilder.h>
#include <utils/qtcassert.h>

namespace EnvFile {

EnvFileSettings::EnvFileSettings() {
  setSettingsGroup("EnvFile");

  enableLoadEnvFile.setSettingsKey("EnableLoadEnvFile");
  enableLoadEnvFile.setLabelText(Tr::tr("Load env file"));
  enableLoadEnvFile.setToolTip(Tr::tr("Auto loads the .env file inthe project's root directory"));
  enableLoadEnvFile.setDefaultValue(true);

  envFilePath.setSettingsKey("EnvFilePath");
  envFilePath.setDefaultValue(".env");
  envFilePath.setExpectedKind(Utils::PathChooser::File);

  auto layout = [this] {
    using namespace Layouting;

    // clang-format off
    return Column {
            enableLoadEnvFile,
            envFilePath
    };
    // clang-format on
  };
  setLayouter(layout);
}

EnvFileSettings &settings() {
  static EnvFileSettings theSettings;
  return theSettings;
}

class EnvFileSettingsPage final : public Core::IOptionsPage {
 public:
  EnvFileSettingsPage() {
    const char SETTINGS_CATEGORY[] = "D.EnvFile";
    const char SETTINGS_ID[] = "A.EnvFile.General";

    setId(SETTINGS_ID);
    setDisplayName(Tr::tr("General"));
    setCategory(SETTINGS_CATEGORY);
    setDisplayCategory(Tr::tr("EnvFile"));
    // setCategoryIconPath(":/fakevim/images/settingscategory_fakevim.png");
    setSettingsProvider([] { return &settings(); });
  }
};

const EnvFileSettingsPage settingsPage;
}  // namespace EnvFile
