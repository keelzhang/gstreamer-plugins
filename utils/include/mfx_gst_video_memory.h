/**********************************************************************************

Copyright (C) 2005-2016 Intel Corporation.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
- Neither the name of Intel Corporation nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL INTEL CORPORATION BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**********************************************************************************/

#ifndef __MFX_GST_VIDEO_MEMORY_H__
#define __MFX_GST_VIDEO_MEMORY_H__

#include "mfx_gst_debug.h"
#include "mfx_gst_utils.h"

#define GST_MFX_FRAME_SURFACE_MEMORY_NAME "mfxFrameSurface"
#define GST_CAPS_FEATURE_MFX_FRAME_SURFACE_MEMORY "memory:mfxFrameSurface"

// TODO these definitions should be hidden
struct GstMfxFrameSurfaceMemory
{
  GstMemory mem;
  mfxFrameSurface1 mfx_surface;
};

struct GstMfxMemoryAllocator
{
  GstAllocator parent;
  MFXFrameAllocator* mfx_allocator;
  mfxFrameAllocRequest request;
  mfxFrameAllocResponse response;
  mfxU32 num_frames_used;
};

struct GstMfxMemoryAllocatorClass
{
  GstAllocatorClass parent_class;
};

#endif
