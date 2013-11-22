/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LATINIME_TERMINAL_POSITION_LOOKUP_TABLE_H
#define LATINIME_TERMINAL_POSITION_LOOKUP_TABLE_H

#include "defines.h"
#include "suggest/policyimpl/dictionary/structure/v4/content/single_dict_content.h"
#include "suggest/policyimpl/dictionary/structure/v4/ver4_dict_constants.h"
#include "utils/hash_map_compat.h"

namespace latinime {

class TerminalPositionLookupTable : public SingleDictContent {
 public:
    typedef hash_map_compat<int, int> TerminalIdMap;

    // TODO: Quit using headerRegionSize.
    TerminalPositionLookupTable(const char *const dictDirPath, const bool isUpdatable,
            const int headerRegionSize)
            : SingleDictContent(dictDirPath,
                      Ver4DictConstants::TERMINAL_ADDRESS_TABLE_FILE_EXTENSION, isUpdatable),
              mSize(getBuffer()->getTailPosition()
                      / Ver4DictConstants::TERMINAL_ADDRESS_TABLE_ADDRESS_SIZE),
              mHeaderRegionSize(headerRegionSize) {}

    TerminalPositionLookupTable() : mSize(0), mHeaderRegionSize(0) {}

    int getTerminalPtNodePosition(const int terminalId) const;

    bool setTerminalPtNodePosition(const int terminalId, const int terminalPtNodePos);

    int getNextTerminalId() const {
        return mSize;
    }

    bool flushToFile(const char *const dictDirPath, const int newHeaderRegionSize) const;

    bool runGCTerminalIds(TerminalIdMap *const terminalIdMap);

 private:
    DISALLOW_COPY_AND_ASSIGN(TerminalPositionLookupTable);

    int getEntryPos(const int terminalId) const {
        return terminalId * Ver4DictConstants::TERMINAL_ADDRESS_TABLE_ADDRESS_SIZE;
    }

    int mSize;
    const int mHeaderRegionSize;
};
} // namespace latinime
#endif // LATINIME_TERMINAL_POSITION_LOOKUP_TABLE_H
