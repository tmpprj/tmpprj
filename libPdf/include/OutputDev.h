//========================================================================
//
// OutputDev.h
//
// Copyright 1996-2003 Glyph & Cog, LLC
//
//========================================================================

#ifndef OUTPUTDEV_H
#define OUTPUTDEV_H

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma interface
#endif

#include "gtypes.h"
#include "CharTypes.h"

class GString;
class GfxState;
struct GfxColor;
class GfxColorSpace;
class GfxImageColorMap;
class GfxFunctionShading;
class GfxAxialShading;
class GfxRadialShading;
class Stream;
class Links;
class Link;
class Catalog;
class Page;
class Function;

//------------------------------------------------------------------------
// OutputDev
//------------------------------------------------------------------------

class OutputDev {
public:

    // Constructor.
    OutputDev() {}

    // Destructor.
    virtual ~OutputDev() {}

    //----- get info about output device

    // Does this device use upside-down coordinates?
    // (Upside-down means (0,0) is the top left corner of the page.)
    virtual GBool upsideDown() = 0;

    // Does this device use drawChar() or drawString()?
    virtual GBool useDrawChar() = 0;

    // Does this device use tilingPatternFill()?  If this returns false,
    // tiling pattern fills will be reduced to a series of other drawing
    // operations.
    virtual GBool useTilingPatternFill() {
        return gFalse;
    }

    // Does this device use functionShadedFill(), axialShadedFill(), and
    // radialShadedFill()?  If this returns false, these shaded fills
    // will be reduced to a series of other drawing operations.
    virtual GBool useShadedFills() {
        return gFalse;
    }

    // Does this device use drawForm()?  If this returns false,
    // form-type XObjects will be interpreted (i.e., unrolled).
    virtual GBool useDrawForm() {
        return gFalse;
    }

    // Does this device use beginType3Char/endType3Char?  Otherwise,
    // text in Type 3 fonts will be drawn with drawChar/drawString.
    virtual GBool interpretType3Chars() = 0;

    // Does this device need non-text content?
    virtual GBool needNonText() {
        return gTrue;
    }

    //----- initialization and control

    // Set default transform matrix.
    virtual void setDefaultCTM(double *ctm);

    // Check to see if a page slice should be displayed.  If this
    // returns false, the page display is aborted.  Typically, an
    // OutputDev will use some alternate means to display the page
    // before returning false.
    virtual GBool checkPageSlice(Page *page, double hDPI, double vDPI,
                                 int rotate, GBool useMediaBox, GBool crop,
                                 int sliceX, int sliceY, int sliceW, int sliceH,
                                 GBool printing, Catalog *catalog,
                                 GBool (*abortCheckCbk)(void *data) = NULL,
                                 void *abortCheckCbkData = NULL)
    {
        boost::ignore_unused_variable_warning( rotate );
        boost::ignore_unused_variable_warning( useMediaBox );
        boost::ignore_unused_variable_warning( crop );
        boost::ignore_unused_variable_warning( sliceH );
        boost::ignore_unused_variable_warning( sliceW );
        boost::ignore_unused_variable_warning( sliceX );
        boost::ignore_unused_variable_warning( sliceY );
        boost::ignore_unused_variable_warning( printing );
        boost::ignore_unused_variable_warning( catalog );
        boost::ignore_unused_variable_warning( abortCheckCbk );
        boost::ignore_unused_variable_warning( abortCheckCbkData );
        boost::ignore_unused_variable_warning( vDPI );
        boost::ignore_unused_variable_warning( hDPI );
        boost::ignore_unused_variable_warning( page );
        return gTrue;
    }

    // Start a page.
    virtual void startPage(int pageNum, GfxState *state)
    {
        boost::ignore_unused_variable_warning( pageNum );
        boost::ignore_unused_variable_warning( state );
    }

    // End a page.
    virtual void endPage() {}

    // Dump page contents to display.
    virtual void dump() {}

    //----- coordinate conversion

    // Convert between device and user coordinates.
    virtual void cvtDevToUser(double dx, double dy, double *ux, double *uy);
    virtual void cvtUserToDev(double ux, double uy, int *dx, int *dy);

    double *getDefCTM() {
        return defCTM;
    }
    double *getDefICTM() {
        return defICTM;
    }

    //----- save/restore graphics state
    virtual void saveState(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void restoreState(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }

    //----- update graphics state
    virtual void updateAll(GfxState *state);
    virtual void updateCTM(GfxState *state, double m11, double m12,
                           double m21, double m22, double m31, double m32)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( m11 );
        boost::ignore_unused_variable_warning( m12 );
        boost::ignore_unused_variable_warning( m21 );
        boost::ignore_unused_variable_warning( m22 );
        boost::ignore_unused_variable_warning( m31 );
        boost::ignore_unused_variable_warning( m32 );
    }
    virtual void updateLineDash(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateFlatness(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateLineJoin(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateLineCap(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateMiterLimit(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateLineWidth(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateStrokeAdjust(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateFillColorSpace(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateStrokeColorSpace(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateFillColor(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateStrokeColor(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateBlendMode(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateFillOpacity(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateStrokeOpacity(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateFillOverprint(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateStrokeOverprint(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateTransfer(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }

    //----- update text state
    virtual void updateFont(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateTextMat(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateCharSpace(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateRender(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateRise(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateWordSpace(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateHorizScaling(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateTextPos(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void updateTextShift(GfxState *state, double shift) {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( shift );
    }

    //----- path painting
    virtual void stroke(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void fill(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void eoFill(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void tilingPatternFill(GfxState *state, Object *str,
                                   int paintType, Dict *resDict,
                                   double *mat, double *bbox,
                                   int x0, int y0, int x1, int y1,
                                   double xStep, double yStep)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( str );
        boost::ignore_unused_variable_warning( paintType );
        boost::ignore_unused_variable_warning( resDict );
        boost::ignore_unused_variable_warning( mat );
        boost::ignore_unused_variable_warning( bbox );
        boost::ignore_unused_variable_warning( x0 );
        boost::ignore_unused_variable_warning( y0 );
        boost::ignore_unused_variable_warning( x1 );
        boost::ignore_unused_variable_warning( y1 );
        boost::ignore_unused_variable_warning( xStep );
        boost::ignore_unused_variable_warning( yStep );
    }
    virtual GBool functionShadedFill(GfxState *state,
                                     GfxFunctionShading *shading)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( shading );
        return gFalse;
    }
    virtual GBool axialShadedFill(GfxState *state, GfxAxialShading *shading)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( shading );
        return gFalse;
    }
    virtual GBool radialShadedFill(GfxState *state, GfxRadialShading *shading)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( shading );
        return gFalse;
    }

    //----- path clipping
    virtual void clip(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void eoClip(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void clipToStrokePath(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }

    //----- text drawing
    virtual void beginStringOp(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void endStringOp(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void beginString(GfxState *state, GString *s) {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( s );
    }
    virtual void endString(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void drawChar(GfxState *state, double x, double y,
                          double dx, double dy,
                          double originX, double originY,
                          CharCode code, int nBytes, Unicode *u, int uLen)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( x );
        boost::ignore_unused_variable_warning( y );
        boost::ignore_unused_variable_warning( dx );
        boost::ignore_unused_variable_warning( dy );
        boost::ignore_unused_variable_warning( originX );
        boost::ignore_unused_variable_warning( originY );
        boost::ignore_unused_variable_warning( code );
        boost::ignore_unused_variable_warning( nBytes );
        boost::ignore_unused_variable_warning( u );
        boost::ignore_unused_variable_warning( uLen );
    }
    virtual void drawString(GfxState *state, GString *s) {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( s);
    }
    virtual GBool beginType3Char(GfxState *state, double x, double y,
                                 double dx, double dy,
                                 CharCode code, Unicode *u, int uLen);
    virtual void endType3Char(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void endTextObject(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }

    //----- image drawing
    virtual void drawImageMask(GfxState *state, Object *ref, Stream *str,
                               int width, int height, GBool invert,
                               GBool inlineImg);
    virtual void drawImage(GfxState *state, Object *ref, Stream *str,
                           int width, int height, GfxImageColorMap *colorMap,
                           int *maskColors, GBool inlineImg);
    virtual void drawMaskedImage(GfxState *state, Object *ref, Stream *str,
                                 int width, int height,
                                 GfxImageColorMap *colorMap,
                                 Stream *maskStr, int maskWidth, int maskHeight,
                                 GBool maskInvert);
    virtual void drawSoftMaskedImage(GfxState *state, Object *ref, Stream *str,
                                     int width, int height,
                                     GfxImageColorMap *colorMap,
                                     Stream *maskStr,
                                     int maskWidth, int maskHeight,
                                     GfxImageColorMap *maskColorMap);

#if OPI_SUPPORT
    //----- OPI functions
    virtual void opiBegin(GfxState *state, Dict *opiDict);
    virtual void opiEnd(GfxState *state, Dict *opiDict);
#endif

    //----- Type 3 font operators
    virtual void type3D0(GfxState *state, double wx, double wy) {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( wx);
        boost::ignore_unused_variable_warning( wy );
    }
    virtual void type3D1(GfxState *state, double wx, double wy,
                         double llx, double lly, double urx, double ury)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( wx );
        boost::ignore_unused_variable_warning( wy );
        boost::ignore_unused_variable_warning( llx );
        boost::ignore_unused_variable_warning( lly );
        boost::ignore_unused_variable_warning( urx );
        boost::ignore_unused_variable_warning( ury );
    }

    //----- form XObjects
    virtual void drawForm(Ref id) {
        boost::ignore_unused_variable_warning( id );
    }

    //----- PostScript XObjects
    virtual void psXObject(Stream *psStream, Stream *level1Stream) {
        boost::ignore_unused_variable_warning( psStream );
        boost::ignore_unused_variable_warning( level1Stream );
    }

    //----- transparency groups and soft masks
    virtual void beginTransparencyGroup(GfxState *state, double *bbox,
                                        GfxColorSpace *blendingColorSpace,
                                        GBool isolated, GBool knockout,
                                        GBool forSoftMask)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( bbox );
        boost::ignore_unused_variable_warning( blendingColorSpace );
        boost::ignore_unused_variable_warning( isolated );
        boost::ignore_unused_variable_warning( knockout );
        boost::ignore_unused_variable_warning( forSoftMask );
    }
    virtual void endTransparencyGroup(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }
    virtual void paintTransparencyGroup(GfxState *state, double *bbox) {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( bbox );
    }
    virtual void setSoftMask(GfxState *state, double *bbox, GBool alpha,
                             Function *transferFunc, GfxColor *backdropColor)
    {
        boost::ignore_unused_variable_warning( state );
        boost::ignore_unused_variable_warning( bbox );
        boost::ignore_unused_variable_warning( alpha);
        boost::ignore_unused_variable_warning( transferFunc);
        boost::ignore_unused_variable_warning( backdropColor );
    }
    virtual void clearSoftMask(GfxState *state) {
        boost::ignore_unused_variable_warning( state );
    }

    //----- links
    virtual void processLink(Link *link, Catalog *catalog) {
        boost::ignore_unused_variable_warning( link );
        boost::ignore_unused_variable_warning( catalog);
    }

#if 1 //~tmp: turn off anti-aliasing temporarily
    virtual GBool getVectorAntialias() {
        return gFalse;
    }
    virtual void setVectorAntialias(GBool vaa) {
        boost::ignore_unused_variable_warning( vaa );
    }
#endif

private:

    double defCTM[6];		// default coordinate transform matrix
    double defICTM[6];		// inverse of default CTM
};

#endif
