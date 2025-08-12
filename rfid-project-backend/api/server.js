// api/server.js
const fs = require("fs");
const path = require("path");
const express = require("express");
const { ethers } = require("ethers");

const app = express();
app.use(express.json());

// Load contract address + ABI
const { address } = JSON.parse(
  fs.readFileSync(path.join(__dirname, "..", "contractAddress.json"), "utf8")
);
const contractABI = require(path.join(
  __dirname,
  "..",
  "artifacts",
  "contracts",
  "TagVerifier.sol",
  "TagVerifier.json"
)).abi;

// Connect to local Hardhat node (read-write)
const provider = new ethers.providers.JsonRpcProvider("http://127.0.0.1:8545");

// Use private key of account with funds — KEEP THIS SECURE!
const signerPriv = "ac0974bec39a17e36ba4a6b4d238ff944bacb478cbed5efcae784d7bf4f2ff80"; // Replace with your real private key
const wallet = new ethers.Wallet(signerPriv, provider);

const contract = new ethers.Contract(address, contractABI, wallet);

console.log("Verification API using contract:", address);

// Verify route - read-only call to contract.verifyTag(tagId)
app.get("/verify/:tagId", async (req, res) => {
  try {
    const tagId = req.params.tagId;
    if (!tagId) return res.status(400).json({ error: "tagId required" });

    const exists = await contract.verifyTag(tagId);
    res.json({ exists: !!exists });
  } catch (err) {
    console.error("verify error:", err);
    res.status(500).json({ error: "Verification failed" });
  }
});

// POST /addTag - sign and send transaction immediately
app.post("/addTag", async (req, res) => {
  try {
    const { tagId } = req.body;
    if (!tagId) return res.status(400).json({ error: "tagId required" });

    console.log("Adding tag:", tagId);

    // Send transaction using ethers wallet + contract
    const tx = await contract.addTag(tagId);

    console.log("Transaction sent. Waiting for confirmation...");
    await tx.wait(); // wait for confirmation

    console.log("Transaction confirmed:", tx.hash);
    res.json({ success: true, txHash: tx.hash });
  } catch (err) {
    console.error("addTag error:", err);
    res.status(500).json({ error: "Failed to add tag" });
  }
});

const PORT = 3000;
app.listen(PORT, "0.0.0.0", () => console.log(`Verification API running on port ${PORT}`));

