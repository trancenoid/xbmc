/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>
#include <vector>

namespace MUSIC_INFO
{
  class CMusicInfoTag;
}

class CFileItem;  // forward

struct LABEL_MASKS
{
  LABEL_MASKS(const std::string& strLabelFile="", const std::string& strLabel2File="", const std::string& strLabelFolder="", const std::string& strLabel2Folder="") :
    m_strLabelFile(strLabelFile),
    m_strLabel2File(strLabel2File),
    m_strLabelFolder(strLabelFolder),
    m_strLabel2Folder(strLabel2Folder)
  {}
  std::string m_strLabelFile;
  std::string m_strLabel2File;
  std::string m_strLabelFolder;
  std::string m_strLabel2Folder;
};

class CLabelFormatter
{
public:
  CLabelFormatter(const std::string &mask, const std::string &mask2);

  void FormatLabel(CFileItem *item) const;
  void FormatLabel2(CFileItem *item) const;
  void FormatLabels(CFileItem *item) const // convenient shorthand
  {
    FormatLabel(item);
    FormatLabel2(item);
  }

  bool FillMusicTag(const std::string &fileName, MUSIC_INFO::CMusicInfoTag *tag) const;

private:
  class CMaskString
  {
  public:
    CMaskString(const std::string &prefix, char content, const std::string &postfix) :
      m_prefix(prefix),
      m_postfix(postfix),
      m_content(content)
    {};
    std::string m_prefix;
    std::string m_postfix;
    char m_content;
  };

  // functions for assembling the mask vectors
  void AssembleMask(unsigned int label, const std::string &mask);
  void SplitMask(unsigned int label, const std::string &mask);

  // functions for retrieving content based on our mask vectors
  std::string GetContent(unsigned int label, const CFileItem *item) const;
  std::string GetMaskContent(const CMaskString &mask, const CFileItem *item) const;
  void FillMusicMaskContent(const char mask, const std::string &value, MUSIC_INFO::CMusicInfoTag *tag) const;

  std::vector<std::string>   m_staticContent[2];
  std::vector<CMaskString>  m_dynamicContent[2];
  bool                 m_hideFileExtensions;
};
