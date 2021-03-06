const cv = global.dut;
const { assertMetaData, assertPropsWithValue, funcShouldRequireArgs, readTestImage } = global.utils;
const { assert, expect } = require('chai');

describe('ximgproc', () => {
  if (!cv.xmodules.ximgproc) {
    it('compiled without ximgproc');
    return;
  }

  let testImg;

  before(() => {
    testImg = readTestImage().resizeToMax(250);
  });

  describe('SuperpixelSEEDS', () => {
    const numSuperpixels = 100;
    const numLevels = 2;

    describe('constructor', () => {
      it('should throw if no args', () => {
        expect(() => new cv.SuperpixelSEEDS()).to.throw('SuperpixelSEEDS::New - Error: expected argument 0 to be of type');
      });

      it('should be constructable with required args', () => {
        const superpixelSeeds = new cv.SuperpixelSEEDS(testImg, numSuperpixels, numLevels);
        expect(superpixelSeeds).to.have.property('img').instanceOf(cv.Mat);
        assertMetaData(testImg)(superpixelSeeds.img);
        assertPropsWithValue(superpixelSeeds)({
          numSuperpixels,
          numLevels
        });
      });
    });

    // TODO: FIX ME
    describe('iterate', () => {
      it('should iterate with default values', () => {
        const superpixelSeeds = new cv.SuperpixelSEEDS(testImg, numSuperpixels, numLevels);
        superpixelSeeds.iterate();
        assert(superpixelSeeds.numCalculatedSuperpixels > 0, 'no superpixels calculated');
        assertPropsWithValue(superpixelSeeds.labels)({
          rows: testImg.rows, cols: testImg.cols, type: cv.CV_32S
        });
      });
    });
  });

  if (cv.version.minor > 0) {
    describe('SuperpixelSLIC', () => {
      const algorithm = cv.SLICO;

      describe('constructor', () => {
        it('should throw if no args', () => {
          expect(() => new cv.SuperpixelSLIC()).to.throw('SuperpixelSLIC::New - Error: expected argument 0 to be of type');
        });

        it('should be constructable with required args', () => {
          const superpixel = new cv.SuperpixelSLIC(testImg, algorithm);
          expect(superpixel).to.have.property('img').instanceOf(cv.Mat);
          assertMetaData(testImg)(superpixel.img);
          assertPropsWithValue(superpixel)({
            algorithm
          });
        });
      });

      describe('iterate', () => {
        it('should iterate with default values', () => {
          const superpixel = new cv.SuperpixelSLIC(testImg, algorithm);
          superpixel.iterate();
          assert(superpixel.numCalculatedSuperpixels > 0, 'no superpixels calculated');
          assertPropsWithValue(superpixel.labels)({
            rows: testImg.rows, cols: testImg.cols, type: cv.CV_32S
          });
        });
      });
    });


    describe('SuperpixelLSC', () => {
      describe('constructor', () => {
        it('should throw if no args', () => {
          expect(() => new cv.SuperpixelLSC()).to.throw('SuperpixelLSC::New - Error: expected argument 0 to be of type');
        });

        it('should be constructable with required args', () => {
          const superpixel = new cv.SuperpixelLSC(testImg);
          expect(superpixel).to.have.property('img').instanceOf(cv.Mat);
          assertMetaData(testImg)(superpixel.img);
        });
      });

      describe('iterate', () => {
        it('should iterate with default values', () => {
          const superpixel = new cv.SuperpixelLSC(testImg);
          superpixel.iterate();
          assert(superpixel.numCalculatedSuperpixels > 0, 'no superpixels calculated');
          assertPropsWithValue(superpixel.labels)({
            rows: testImg.rows, cols: testImg.cols, type: cv.CV_32S
          });
        });
      });
    });
  }
});
