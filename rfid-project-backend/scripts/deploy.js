const fs = require("fs");

async function main() {
  const TagVerifier = await ethers.getContractFactory("TagVerifier");
  const verifier = await TagVerifier.deploy();
  await verifier.deployed();

  console.log(`TagVerifier deployed to: ${verifier.address}`);

  // Save contract address to a JSON file
  const contractInfo = {
    address: verifier.address,
    network: "localhost" // change to "sepolia", "matic", etc. if needed
  };
  fs.writeFileSync("contractAddress.json", JSON.stringify(contractInfo, null, 2));

  // Optional: Add some test UIDs
  await verifier.addTag("1234ABCD");
  await verifier.addTag("5678EFGH");
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
