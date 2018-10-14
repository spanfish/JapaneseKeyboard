// Copyright 2010-2014, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_WIN32_BASE_TSF_REGISTRAR_H_
#define MOZC_WIN32_BASE_TSF_REGISTRAR_H_

#include <windows.h>

#include "base/port.h"

namespace mozc {
namespace win32 {

// Registers Mozc as a text input processor or unregister.
class TsfRegistrar {
 public:
  // Registers the DLL specified with |path| as a COM server.
  static HRESULT RegisterCOMServer(const wchar_t *path, DWORD path_length);

  // Unregisters the DLL from registry.
  static void UnregisterCOMServer();

  // Registers this COM server to the profile store for input processors.
  // The caller is responsible for initializing COM before call this function.
  static HRESULT RegisterProfiles(const wchar_t *path, DWORD path_length);

  // Unregisters this COM server from the text service framework.
  // The caller is responsible for initializing COM before call this function.
  static void UnregisterProfiles();

  // Retrieves the category manager for text input processors, and
  // registers this module as a keyboard and a display attribute provider.
  // The caller is responsible for initializing COM before call this function.
  static HRESULT RegisterCategories();

  // Retrieves the category manager for text input processors, and unregisters
  // this keyboard module.
  // The caller is responsible for initializing COM before call this function.
  static void UnregisterCategories();

  // Retrieves if the text input processor profile is enabled or not.
  // This function sets FALSE to |enable| if the profile is not installed.
  // The caller is responsible for initializing COM before call this function.
  static HRESULT GetProfileEnabled(BOOL *enabled);

  // Enables or disables the text input processor profile.
  // The caller is responsible for initializing COM before call this function.
  static HRESULT SetProfileEnabled(BOOL enable);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(TsfRegistrar);
};
}  // namespace win32
}  // namespace mozc

#endif  // MOZC_WIN32_BASE_TSF_REGISTRAR_H_
