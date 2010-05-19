// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_EXTENSION_FILE_UTIL_H_
#define CHROME_COMMON_EXTENSIONS_EXTENSION_FILE_UTIL_H_

#include <set>
#include <string>

#include "base/file_path.h"
#include "chrome/common/extensions/extension.h"

class ExtensionMessageBundle;

// Utilties for manipulating the on-disk storage of extensions.
namespace extension_file_util {

// The name of the directory inside the profile that we store installed
// extension in.
extern const char kInstallDirectoryName[];

// Copies |unpacked_source_dir| into the right location under |extensions_dir|.
// The destination directiory is returned on success, or empty path is returned
// on failure.
FilePath InstallExtension(const FilePath& unpacked_source_dir,
                          const std::string& id,
                          const std::string& version,
                          const FilePath& extensions_dir);

// Removes all versions of the extension with |id| from |extensions_dir|.
void UninstallExtension(const FilePath& extensions_dir,
                        const std::string& id);

// Loads and validates an extension from the specified directory. Returns NULL
// on failure, with a description of the error in |error|.
Extension* LoadExtension(const FilePath& extension_root,
                         bool require_key,
                         std::string* error);

// Returns true if the given extension object is valid and consistent.
// Otherwise, a description of the error is returned in |error|.
bool ValidateExtension(Extension* extension, std::string* error);

// Cleans up the extension install directory. It can end up with garbage in it
// if extensions can't initially be removed when they are uninstalled (eg if a
// file is in use).
//
// |extensions_dir| is the install directory to look in. |extension_paths| is a
// map from extension id to full installation path.
//
// Obsolete version directories are removed, as are directories that aren't
// found in |extension_paths|.
void GarbageCollectExtensions(
    const FilePath& extensions_dir,
    const std::map<std::string, FilePath>& extension_paths);

// Loads extension message catalogs and returns message bundle.
// Returns NULL on error, or if extension is not localized.
ExtensionMessageBundle* LoadExtensionMessageBundle(
    const FilePath& extension_path,
    const std::string& default_locale,
    std::string* error);

// We need to reserve the namespace of entries that start with "_" for future
// use by Chrome.
// If any files or directories are found using "_" prefix and are not on
// reserved list we return false, and set error message.
bool CheckForIllegalFilenames(const FilePath& extension_path,
                              std::string* error);

// Get a relative file path from a chrome-extension:// URL.
FilePath ExtensionURLToRelativeFilePath(const GURL& url);

}  // extension_file_util

#endif  // CHROME_COMMON_EXTENSIONS_EXTENSION_FILE_UTIL_H_
