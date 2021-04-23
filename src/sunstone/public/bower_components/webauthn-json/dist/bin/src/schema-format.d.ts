declare type SchemaLeaf = "copy" | "convert";
interface SchemaObject {
    [property: string]: {
        required: boolean;
        schema: Schema;
    };
}
declare type SchemaArray = [SchemaObject] | [SchemaLeaf];
export declare type Schema = SchemaLeaf | SchemaArray | SchemaObject;
export declare const copyValue = "copy";
export declare const convertValue = "convert";
export declare function convert<From, To>(conversionFn: (v: From) => To, schema: Schema, input: any): any;
export declare function required(schema: Schema): any;
export declare function optional(schema: Schema): any;
export {};
//# sourceMappingURL=schema-format.d.ts.map