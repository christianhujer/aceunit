/* Copyright (c) 2007 - 2011, Christian Hujer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the AceUnit developers nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** Mini Ram Logger implementation that logs messages to RAM with as little memory consumption as possible.
 * The format of the messages is suitable for postprocessing to convert it into the same format as that of #FullPlainLogger.c.
 * This Logger also could serve as a template if you want to create your own logger that e.g. logs by writing to a NVM like EEPROM or Flash.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file MiniRamLogger.c
 */

#ifdef ACEUNIT_MINIRAMLOGGER_SAVE
#include <stdio.h>
#endif
#include <string.h>

#ifndef ACEUNIT_MINIRAM_LOGGER_BUFSIZE
/** The size of the buffer that's used for the Mini Ram Logger. */
#define ACEUNIT_MINIRAM_LOGGER_BUFSIZE 32
#endif

#include "AceUnit.h"
#include "AceUnitLogging.h"
#ifndef ACEUNIT_EMBEDDED
#error "MiniRamLogger can only be used for ACEUNIT_EMBEDDED."
#endif

/** The number of valid logging elements in #data. */
/* Linkage note: RAM. */
size_t elementCount;

/** AceUnit Mini Ram Logger data buffer. */
/* Linkage note: RAM. */
AssertionError_t data[ACEUNIT_MINIRAM_LOGGER_BUFSIZE];

/** Initializes the Mini Ram Logger. */
void MiniRamLoggerInit() {
    elementCount = 0;
    memset(data, 0, sizeof(data));
}

/** Logs a message using this logger.
 * @param recentError Error to log.
 */
void MiniRamLoggerLog(const AssertionError_t *const recentError) {
    data[elementCount++] = *recentError;
}

#ifdef ACEUNIT_MINIRAMLOGGER_SAVE
/** Writes contents of the Mini Ram Logger to a file.
 * @param file File to write to.
 */
void MiniRamLoggerSave(FILE *file) {
    /* The file will first contain a BOM (byte order mark).
     * That enables tools that read this file to find out whether it was written in Big Endian or Little Endian.
     */
    uint16_t bom = 0xFFFE;
    fwrite(&bom, sizeof(uint16_t), 1, file);

    /* Now write the data. */
    fwrite(data, sizeof(AssertionError_t), elementCount, file);
}
#endif

/** This Logger. */
AceUnitNewLogger(MiniRamLogger,
    NULL,
    NULL,
    NULL,
    NULL,
    MiniRamLoggerLog,
    NULL,
    NULL,
    NULL,
    NULL
);

TestLogger_t *globalLogger = &MiniRamLogger; /* XXX Hack. Remove. */
