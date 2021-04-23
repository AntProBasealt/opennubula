import { Base64urlString } from "./base64url";
export interface PublicKeyCredentialDescriptorJSON {
    type: PublicKeyCredentialType;
    id: Base64urlString;
    transports?: AuthenticatorTransport[];
}
interface WebAuthnExtensionsJSON {
    appid?: string;
    txAuthSimple?: string;
    txAuthGeneric?: {
        contentType: string;
        content: Base64urlString;
    };
    authnSel?: Base64urlString[];
    exts?: boolean;
    uvi?: boolean;
    loc?: boolean;
    uvm?: boolean;
    authenticatorBiometricPerfBounds?: {
        FAR: number;
        FRR: number;
    };
}
interface PublicKeyCredentialUserEntityJSON extends PublicKeyCredentialEntity {
    displayName: string;
    id: Base64urlString;
}
interface PublicKeyCredentialCreationOptionsJSON {
    rp: PublicKeyCredentialRpEntity;
    user: PublicKeyCredentialUserEntityJSON;
    challenge: Base64urlString;
    pubKeyCredParams: PublicKeyCredentialParameters[];
    timeout?: number;
    excludeCredentials?: PublicKeyCredentialDescriptorJSON[];
    authenticatorSelection?: AuthenticatorSelectionCriteria;
    attestation?: AttestationConveyancePreference;
    extensions?: WebAuthnExtensionsJSON;
}
export interface CredentialCreationOptionsJSON {
    publicKey: PublicKeyCredentialCreationOptionsJSON;
    signal?: AbortSignal;
}
interface AuthenticatorAttestationResponseJSON {
    clientDataJSON: Base64urlString;
    attestationObject: Base64urlString;
}
export interface PublicKeyCredentialWithAttestationJSON {
    id: string;
    type: PublicKeyCredentialType;
    rawId: Base64urlString;
    response: AuthenticatorAttestationResponseJSON;
    clientExtensionResults: AuthenticationExtensionsClientOutputs;
}
interface PublicKeyCredentialRequestOptionsJSON {
    challenge: Base64urlString;
    timeout?: number;
    rpId?: string;
    allowCredentials?: PublicKeyCredentialDescriptorJSON[];
    userVerification?: UserVerificationRequirement;
    extensions?: WebAuthnExtensionsJSON;
}
export interface CredentialRequestOptionsJSON {
    mediation?: CredentialMediationRequirement;
    publicKey?: PublicKeyCredentialRequestOptionsJSON;
    signal?: AbortSignal;
}
interface AuthenticatorAssertionResponseJSON {
    clientDataJSON: Base64urlString;
    authenticatorData: Base64urlString;
    signature: Base64urlString;
    userHandle: Base64urlString | null;
}
export interface PublicKeyCredentialWithAssertionJSON {
    type: PublicKeyCredentialType;
    id: string;
    rawId: Base64urlString;
    response: AuthenticatorAssertionResponseJSON;
    clientExtensionResults: AuthenticationExtensionsClientOutputs;
}
export {};
//# sourceMappingURL=json.d.ts.map