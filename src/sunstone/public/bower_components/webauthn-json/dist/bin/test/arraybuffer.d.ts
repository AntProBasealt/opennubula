/// <reference types="jest" />
declare global {
    namespace jest {
        interface Matchers<R> {
            toEqualBuffer(observed: ArrayBuffer): CustomMatcherResult;
        }
    }
}
export {};
//# sourceMappingURL=arraybuffer.d.ts.map