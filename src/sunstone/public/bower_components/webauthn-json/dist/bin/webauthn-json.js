#!/usr/bin/env node
const version="0.4.0-beta.1";!function(e){"function"==typeof define&&define.amd?define(e):e()}(function(){"use strict";function e(e){return{required:!0,schema:e}}function t(e){return{required:!1,schema:e}}const o={type:e("copy"),id:e("convert"),transports:t("copy")},c={appid:t("copy"),txAuthSimple:t("copy"),txAuthGeneric:t({contentType:e("copy"),content:e("convert")}),authnSel:t(["convert"]),exts:t("copy"),uvi:t("copy"),loc:t("copy"),uvm:t("copy"),authenticatorBiometricPerfBounds:t("copy")},n={credentialCreationOptions:{publicKey:e({rp:e("copy"),user:e({id:e("convert"),name:e("copy"),displayName:e("copy"),icon:t("copy")}),challenge:e("convert"),pubKeyCredParams:e("copy"),timeout:t("copy"),excludeCredentials:t([o]),authenticatorSelection:t("copy"),attestation:t("copy"),extensions:t(c)}),signal:t("copy")},publicKeyCredentialWithAttestation:{type:e("copy"),id:e("copy"),rawId:e("convert"),response:e({clientDataJSON:e("convert"),attestationObject:e("convert")})},credentialRequestOptions:{mediation:t("copy"),publicKey:e({challenge:e("convert"),timeout:t("copy"),rpId:t("copy"),allowCredentials:t([o]),userVerification:t("copy"),extensions:t(c)}),signal:t("copy")},publicKeyCredentialWithAssertion:{type:e("copy"),id:e("copy"),rawId:e("convert"),response:e({clientDataJSON:e("convert"),authenticatorData:e("convert"),signature:e("convert"),userHandle:e("convert")})}},i=`Usage: ${process.argv[1]} schema`;if("schema"===process.argv[2]){const e=Object.assign(Object.assign({},n),{version:version});console.log(JSON.stringify(e,null,"  "))}else console.log(i)});
//# sourceMappingURL=webauthn-json.js.map