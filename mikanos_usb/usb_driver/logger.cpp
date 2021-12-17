#include "logger.hpp"
#include "rust_support.hpp"

#include <cstddef>
#include <cstdio>
#include <string.h>

//#include "console.hpp"

namespace {
  LogLevel log_level = kWarn;
}

//extern Console* console;

char log_buf[65536] = "";

extern "C" void SetLogLevel(LogLevel level) {
  log_level = level;
}

int Log(LogLevel level, const char* format, ...) {
  // if (level > log_level) {
  //   return 0;
  // }

  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  //console->PutString(s);
  usb_log(level, s, strlen(s));
  if (strlen(log_buf) + strlen(s) + 1 > 65536) {
    return 0;
  }
  strcat(log_buf, s);

  return result;
}

extern "C" char *GetLog() {
  return log_buf;
}

extern "C" void ClearLog() {
  strcpy(log_buf, "");
}
