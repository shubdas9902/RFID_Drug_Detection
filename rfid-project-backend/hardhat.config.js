require("@nomiclabs/hardhat-ethers");
require("dotenv").config();

const { PRIVATE_KEY, ALCHEMY_URL } = process.env;

module.exports = {
  solidity: "0.8.28", // match your contract pragma version
  networks: {
    sepolia: {
      url: ALCHEMY_URL,
      accounts: [`0x${PRIVATE_KEY}`]
    }
  }
};
