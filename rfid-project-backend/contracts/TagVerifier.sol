// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract TagVerifier {
    mapping(string => bool) public validTags;

    function addTag(string memory uid) public {
        validTags[uid] = true;
    }

    function verifyTag(string memory uid) public view returns (bool) {
        return validTags[uid];
    }
}
