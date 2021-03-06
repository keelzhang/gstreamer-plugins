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

#ifndef __VAAPI_UTILS_H__
#define __VAAPI_UTILS_H__

#ifdef LIBVA_SUPPORT

#include <va/va.h>
#include <va/va_drmcommon.h>

#if defined(LIBVA_DRM_SUPPORT)
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <libdrm/intel_bufmgr.h>
#include <va/va_drm.h>
#endif
#if defined(LIBVA_X11_SUPPORT)
#include <va/va_x11.h>
#endif

#include <mfxdefs.h>

enum LibVABackend
{
    MFX_LIBVA_AUTO,
    MFX_LIBVA_DRM,
    MFX_LIBVA_X11,
    MFX_LIBVA_WAYLAND
};

namespace MfxLoader
{

    class SimpleLoader
    {
    public:
        SimpleLoader(const char * name);

        void * GetFunction(const char * name);

        ~SimpleLoader();

    private:
        SimpleLoader(SimpleLoader&);
        void operator=(SimpleLoader&);

        void * so_handle;
    };

#ifdef LIBVA_SUPPORT
    class VA_Proxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef VAStatus (*vaInitialize_type)(VADisplay, int *, int *);
        typedef VAStatus (*vaTerminate_type)(VADisplay);
        typedef VAStatus (*vaCreateSurfaces_type)(VADisplay, unsigned int,
            unsigned int, unsigned int, VASurfaceID *, unsigned int,
            VASurfaceAttrib *, unsigned int);
        typedef VAStatus (*vaDestroySurfaces_type)(VADisplay, VASurfaceID *, int);
        typedef VAStatus (*vaCreateBuffer_type)(VADisplay, VAContextID,
            VABufferType, unsigned int, unsigned int, void *, VABufferID *);
        typedef VAStatus (*vaDestroyBuffer_type)(VADisplay, VABufferID);
        typedef VAStatus (*vaMapBuffer_type)(VADisplay, VABufferID, void **pbuf);
        typedef VAStatus (*vaUnmapBuffer_type)(VADisplay, VABufferID);
        typedef VAStatus (*vaSyncSurface_type)(VADisplay, VASurfaceID);
        typedef VAStatus (*vaDeriveImage_type)(VADisplay, VASurfaceID, VAImage *);
        typedef VAStatus (*vaDestroyImage_type)(VADisplay, VAImageID);
        typedef VAStatus (*vaGetLibFunc_type)(VADisplay, const char *func);
#ifndef DISABLE_VAAPI_BUFFER_EXPORT
        typedef VAStatus (*vaAcquireBufferHandle_type)(VADisplay, VABufferID, VABufferInfo *);
        typedef VAStatus (*vaReleaseBufferHandle_type)(VADisplay, VABufferID);
#endif

        VA_Proxy();
        ~VA_Proxy();

        const vaInitialize_type      vaInitialize;
        const vaTerminate_type       vaTerminate;
        const vaCreateSurfaces_type  vaCreateSurfaces;
        const vaDestroySurfaces_type vaDestroySurfaces;
        const vaCreateBuffer_type    vaCreateBuffer;
        const vaDestroyBuffer_type   vaDestroyBuffer;
        const vaMapBuffer_type       vaMapBuffer;
        const vaUnmapBuffer_type     vaUnmapBuffer;
        const vaSyncSurface_type     vaSyncSurface;
        const vaDeriveImage_type     vaDeriveImage;
        const vaDestroyImage_type    vaDestroyImage;
        const vaGetLibFunc_type      vaGetLibFunc;
#ifndef DISABLE_VAAPI_BUFFER_EXPORT
        const vaAcquireBufferHandle_type vaAcquireBufferHandle;
        const vaReleaseBufferHandle_type vaReleaseBufferHandle;
#endif
    };
#endif

#if defined(LIBVA_DRM_SUPPORT)
    class DRM_Proxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef int (*drmIoctl_type)(int fd, unsigned long request, void *arg);
        typedef int (*drmModeAddFB_type)(
          int fd, uint32_t width, uint32_t height, uint8_t depth,
          uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
          uint32_t *buf_id);
        typedef void (*drmModeFreeConnector_type)( drmModeConnectorPtr ptr );
        typedef void (*drmModeFreeCrtc_type)( drmModeCrtcPtr ptr );
        typedef void (*drmModeFreeEncoder_type)( drmModeEncoderPtr ptr );
        typedef void (*drmModeFreePlane_type)( drmModePlanePtr ptr );
        typedef void (*drmModeFreePlaneResources_type)(drmModePlaneResPtr ptr);
        typedef void (*drmModeFreeResources_type)( drmModeResPtr ptr );
        typedef drmModeConnectorPtr (*drmModeGetConnector_type)(
          int fd, uint32_t connectorId);
        typedef drmModeCrtcPtr (*drmModeGetCrtc_type)(int fd, uint32_t crtcId);
        typedef drmModeEncoderPtr (*drmModeGetEncoder_type)(int fd, uint32_t encoder_id);
        typedef drmModePlanePtr (*drmModeGetPlane_type)(int fd, uint32_t plane_id);
        typedef drmModePlaneResPtr (*drmModeGetPlaneResources_type)(int fd);
        typedef drmModeResPtr (*drmModeGetResources_type)(int fd);
        typedef int (*drmModeRmFB_type)(int fd, uint32_t bufferId);
        typedef int (*drmModeSetCrtc_type)(
          int fd, uint32_t crtcId, uint32_t bufferId,
          uint32_t x, uint32_t y, uint32_t *connectors, int count,
          drmModeModeInfoPtr mode);
        typedef int (*drmSetMaster_type)(int fd);
        typedef int (*drmDropMaster_type)(int fd);
        typedef int (*drmModeSetPlane_type)(
          int fd, uint32_t plane_id, uint32_t crtc_id,
          uint32_t fb_id, uint32_t flags,
          int32_t crtc_x, int32_t crtc_y,
          uint32_t crtc_w, uint32_t crtc_h,
          uint32_t src_x, uint32_t src_y,
          uint32_t src_w, uint32_t src_h);

        DRM_Proxy();
        ~DRM_Proxy();

#define __DECLARE(name) const name ## _type name
        __DECLARE(drmIoctl);
        __DECLARE(drmModeAddFB);
        __DECLARE(drmModeFreeConnector);
        __DECLARE(drmModeFreeCrtc);
        __DECLARE(drmModeFreeEncoder);
        __DECLARE(drmModeFreePlane);
        __DECLARE(drmModeFreePlaneResources);
        __DECLARE(drmModeFreeResources);
        __DECLARE(drmModeGetConnector);
        __DECLARE(drmModeGetCrtc);
        __DECLARE(drmModeGetEncoder);
        __DECLARE(drmModeGetPlane);
        __DECLARE(drmModeGetPlaneResources);
        __DECLARE(drmModeGetResources);
        __DECLARE(drmModeRmFB);
        __DECLARE(drmModeSetCrtc);
        __DECLARE(drmSetMaster);
        __DECLARE(drmDropMaster);
        __DECLARE(drmModeSetPlane);
#undef __DECLARE
    };

    class DrmIntel_Proxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef drm_intel_bo* (*drm_intel_bo_gem_create_from_prime_type)(
          drm_intel_bufmgr *bufmgr, int prime_fd, int size);
        typedef void (*drm_intel_bo_unreference_type)(drm_intel_bo *bo);
        typedef drm_intel_bufmgr* (*drm_intel_bufmgr_gem_init_type)(int fd, int batch_size);

        DrmIntel_Proxy();
        ~DrmIntel_Proxy();

#define __DECLARE(name) const name ## _type name
        __DECLARE(drm_intel_bo_gem_create_from_prime);
        __DECLARE(drm_intel_bo_unreference);
        __DECLARE(drm_intel_bufmgr_gem_init);

#undef __DECLARE
    };

    class VA_DRMProxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef VADisplay (*vaGetDisplayDRM_type)(int);


        VA_DRMProxy();
        ~VA_DRMProxy();

        const vaGetDisplayDRM_type vaGetDisplayDRM;
    };
#endif

#if defined (LIBVA_WAYLAND_SUPPORT)

    class Wayland;

    class VA_WaylandClientProxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef    Wayland* (*WaylandCreate_type)(void);

        VA_WaylandClientProxy();
        ~VA_WaylandClientProxy();

        const WaylandCreate_type WaylandCreate;
    };

#endif // LIBVA_WAYLAND_SUPPORT

#if defined(LIBVA_X11_SUPPORT)
    class VA_X11Proxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef VADisplay (*vaGetDisplay_type)(Display*);
        typedef VAStatus (*vaPutSurface_type)(
            VADisplay, VASurfaceID,
            Drawable,
            short, short,
            unsigned short, unsigned short,
            short, short,
            unsigned short, unsigned short,
            VARectangle *,
            unsigned int, unsigned int);

        VA_X11Proxy();
        ~VA_X11Proxy();

        const vaGetDisplay_type vaGetDisplay;
        const vaPutSurface_type vaPutSurface;
    };

    class XLib_Proxy
    {
    private:
        SimpleLoader lib; // should appear first in member list

    public:
        typedef Display* (*XOpenDisplay_type) (char*);
        typedef int (*XCloseDisplay_type)(Display*);
        typedef Window (*XCreateSimpleWindow_type)(Display *,
            Window, int, int,
            unsigned int, unsigned int,
            unsigned int, unsigned long,
            unsigned long);
        typedef int (*XMapWindow_type)(Display*, Window);
        typedef int (*XSync_type)(Display*, Bool);
        typedef int (*XDestroyWindow_type)(Display*, Window);
        typedef int (*XResizeWindow_type)(Display *, Window, unsigned int, unsigned int);

        XLib_Proxy();
        ~XLib_Proxy();

        const XOpenDisplay_type        XOpenDisplay;
        const XCloseDisplay_type       XCloseDisplay;
        const XCreateSimpleWindow_type XCreateSimpleWindow;
        const XMapWindow_type          XMapWindow;
        const XSync_type               XSync;
        const XDestroyWindow_type      XDestroyWindow;
        const XResizeWindow_type       XResizeWindow;
    };
#endif
} // namespace MfxLoader


typedef VAStatus (*vaExtGetSurfaceHandle)(
    VADisplay dpy,
    VASurfaceID *surface,
    int *prime_fd);

#define VPG_EXT_GET_SURFACE_HANDLE "vpgExtGetSurfaceHandle"


class CLibVA
{
public:
    virtual ~CLibVA(void) {};

    VAStatus AcquireVASurface(
        void** pctx,
        VADisplay dpy1,
        VASurfaceID srf1,
        VADisplay dpy2,
        VASurfaceID* srf2);
    void ReleaseVASurface(
        void* actx,
        VADisplay dpy1,
        VASurfaceID /*srf1*/,
        VADisplay dpy2,
        VASurfaceID srf2);

    inline int getBackendType() { return m_type; }
    VADisplay GetVADisplay(bool render = false)
     { return (render && m_va_dpy_render)? m_va_dpy_render: m_va_dpy; }
    const MfxLoader::VA_Proxy m_libva;

protected:
    CLibVA(int type)
      : m_type(type)
      , m_va_dpy(NULL)
    {}
    int m_type;
    VADisplay m_va_dpy;
    VADisplay m_va_dpy_render;

    vaExtGetSurfaceHandle m_fnVaGetSurfaceHandle;

private:
    CLibVA(const CLibVA&);
    CLibVA& operator=(const CLibVA&);
};

#define IHD_DRV_VIDEO_DRIVER "iHD_drv_video.so"

CLibVA* CreateLibVA(int type = MFX_LIBVA_DRM);

VAStatus AcquireVASurface(void** ctx, VADisplay dpy1, VASurfaceID srf1, VADisplay dpy2, VASurfaceID* srf2);
void ReleaseVASurface(void* actx, VADisplay dpy1, VASurfaceID srf1, VADisplay dpy2, VASurfaceID srf2);

mfxStatus va_to_mfx_status(VAStatus va_res);

#endif // #ifdef LIBVA_SUPPORT

#endif // #ifndef __VAAPI_UTILS_H__
