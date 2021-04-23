import { CredentialCreationOptionsJSON, CredentialRequestOptionsJSON, PublicKeyCredentialWithAssertionJSON, PublicKeyCredentialWithAttestationJSON } from "./json";
export declare function create(requestJSON: CredentialCreationOptionsJSON): Promise<PublicKeyCredentialWithAttestationJSON>;
export declare function get(requestJSON: CredentialRequestOptionsJSON): Promise<PublicKeyCredentialWithAssertionJSON>;
declare global {
    interface Window {
        PublicKeyCredential: PublicKeyCredential | undefined;
    }
}
export declare function supported(): boolean;
//# sourceMappingURL=webauthn.d.ts.map