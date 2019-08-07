// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The DUTCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
// This is comment

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints = 

    boost::assign::map_list_of

    (0, uint256("0x00000e02346c923297b2d2c698fb304357350e1b2941bab0cebe439f07c7e18b"))
    (2, uint256("0x3c2dd6ea48e899c66dcfae2de120dac7b1ad299b5f5a4c7a3b7880e034f5471a")) //premine block
    (1000, uint256("0x0000004e1b876678b6def9d7405d49cc32c64eb5a7a150ec0a2fffcc3488892f")) // last POW block
    (1001, uint256("0xe1d455e53c079d4ad3c55e357abf4e9694a5764aa839ea98529146213c375f3c")) // first POS block
    (2000, uint256("0x07e57768b9f91048a25ed580fc45cebea594f6020bd654c908a77a6a3281db6d"))
    (3000, uint256("0xa3d7d80ffd4f87edc6566428dd55806711ff7df924be16d6d6247e9a6656b8cc"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1565134237, // * UNIX timestamp of last checkpoint block
    5004,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000003405e23305b027802a02638e93ce2c97c3e65dc9249fe7ed447442e77af"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1564478820,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x0344fb6af13f422f3885ce9b73fe38404813cd009aa230e190d9237231d5e201"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1564478880,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x44; // D
        pchMessageStart[1] = 0x55; // U
        pchMessageStart[2] = 0x54; // T
        pchMessageStart[3] = 0x43; // C
        vAlertPubKey = ParseHex("04e669fedfb9522bda86f394c3c3be4e976cad1d98ca53173ead82aba028f64e2b12fc1cc736adb16ae1fa498081ad3e47bc82e52036cfccf31ceb22da71d3d836");
        nDefaultPort = 31719; //p2p port
        bnProofOfWorkLimit = ~uint256(0) >> 1;        
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // DUTCOIN: 1 day
        nTargetSpacing = 1 * 60;  // DUTCOIN: 1 minutes
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 760000000 * COIN;
		
		 

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 1; // we use the version 2 for DUT

        const char* pszTimestamp = "The Economic Times: Banning cryptocurrencies in India not the solution: Nasscom";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f92d9ba234cd41b3d2366756d4cf218fd9dae1ba7eff4a524c0752fb7f52802745f5eb0170cb0c170297d6f0753594f4102aff4a1a1e1c0ebc1203f4c27e1eba") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1564478760;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 761804; 

        hashGenesisBlock = genesis.GetHash();          

        assert(hashGenesisBlock == uint256("0x00000e02346c923297b2d2c698fb304357350e1b2941bab0cebe439f07c7e18b"));
        assert(genesis.hashMerkleRoot == uint256("0xac4152dc4e30c16213027884498dcec6784ef72281c40651ac4b19e004b4829f"));
        
        vSeeds.push_back(CDNSSeedData("exdut.com", "exdut.com"));
        vSeeds.push_back(CDNSSeedData("62.151.182.181", "62.151.182.181"));
        vSeeds.push_back(CDNSSeedData("62.151.178.33", "62.151.178.33"));
	    vSeeds.push_back(CDNSSeedData("74.208.183.29", "74.208.183.29"));		


        // DUTCOIN addresses start with 'D'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        // DUTCOIN script addresses start with 'M'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 50);
        // DUTCOIN private keys start with 'E'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 90);
        // DUTCOIN BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // DUTCOIN BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // DUTCOIN BIP44 coin type is '119' (0x80000077)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0412795bbc908fc686d4e6625f75023b22ba54e21f9461030ee166344786954903a9d8d07b68f654c98094f236b257d0cfd5f8080b3367020b660a796e6adf94a1";
        strMasternodePoolDummyAddress = "D9L54eBuv2YfTQYwfRuY2ESPvZ4eTuKdmq";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64; // d
        pchMessageStart[1] = 0x75; // u
        pchMessageStart[2] = 0x74; // t
        pchMessageStart[3] = 0x63; // c
        vAlertPubKey = ParseHex("04893270300589d577a2287fe8e077aa2734fef19ae4230ad1d2b4401b01ef5a6ac757c294e54df6b2a3545c8065147c2342007883a643d862e8069a879bd89344");
        nDefaultPort = 31720;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // DUTCOIN: 1 day
        nTargetSpacing = 2 * 60;  // DUTCOIN: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 760000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1564478820;
        genesis.nNonce = 53362;               
        
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000003405e23305b027802a02638e93ce2c97c3e65dc9249fe7ed447442e77af"));
        assert(genesis.hashMerkleRoot == uint256("0xac4152dc4e30c16213027884498dcec6784ef72281c40651ac4b19e004b4829f"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.	
        
        // Testnet DUTCOIN addresses start with 't'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 90);
        // Testnet DUTCOIN script addresses start with 'm'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 110);
        // Testnet private keys start with 'G'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 105);
        // Testnet DUTCOIN BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet DUTCOIN BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet DUTCOIN BIP44 coin type is '119' (0x80000077)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "047570bdf4ddbae29f64744a520000450996ecddc7d784c7129bf4411d68d2c74c1db2144b34d051f972b97a7b113faabe466fc4becdd1248b98eb2d2d6c517715";
        strMasternodePoolDummyAddress = "dVKARSXCe8MxJ49CAxTBq5UAezmmowQ7pg";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x72; // r
        pchMessageStart[1] = 0x65; // e
        pchMessageStart[2] = 0x67; // g
        pchMessageStart[3] = 0x74; // t
        nDefaultPort = 31721;        
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // DUTCOIN: 1 day
        nTargetSpacing = 1 * 60;        // DUTCOIN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1564478880;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 11;
        

        hashGenesisBlock = genesis.GetHash();

       assert(hashGenesisBlock == uint256("0x0344fb6af13f422f3885ce9b73fe38404813cd009aa230e190d9237231d5e201"));
       assert(genesis.hashMerkleRoot == uint256("0xac4152dc4e30c16213027884498dcec6784ef72281c40651ac4b19e004b4829f"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        // Testnet DUTCOIN addresses start with 'R'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60);
        // Testnet DUTCOIN script addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 125);
        // Testnet private keys start with 'J'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 120);
        // Testnet DUTCOIN BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet DUTCOIN BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet DUTCOIN BIP44 coin type is '119' (0x80000077)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 22223;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases    
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}        
