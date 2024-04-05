#ifndef ENVFILESETTINGS_H
#define ENVFILESETTINGS_H

#include <utils/aspects.h>

namespace EnvFile {

struct Tr {
  Q_DECLARE_TR_FUNCTIONS(QtC::EnvFile)
};

class EnvFileSettings : public Utils::AspectContainer {
 public:
  EnvFileSettings();

  Utils::BoolAspect enableLoadEnvFile{this};
  Utils::StringAspect envFilePattern{this};
};

EnvFileSettings &settings();

}  // namespace EnvFile

#endif  // ENVFILESETTINGS_H
