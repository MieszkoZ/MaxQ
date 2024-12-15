// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceData.h
// 
// API Comments
// 
// Purpose:  C++ Data stuff
// (kernel file reading, etc.)
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceData.h is part of the "refined C++ API".
//------------------------------------------------------------------------------

/**
 * @mz
 * Source documentation:
 *	https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/index.html
 *	https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/mostused.html
 * Function renames proposition:
 *	Furnsh - Furnish
 *	Bodvrd - BodyValueRead
 *	Gdpool -
 *	Bods2c - BodyStringToIDCode
 *	Bodc2n - BodyIDCodeToName
 */

#pragma once

#include "SpiceStructs.h"


enum class ES_ResultCode : uint8;

namespace MaxQ::Data
{
	SPICE_API TArray<FString> EnumerateDirectory(
		const FString& relativeDirectory = TEXT("NonAssetData/kernels"),
		bool ErrorIfNoFilesFound = true,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	SPICE_API bool FurnshDirectory(
		const FString& relativeDirectory = TEXT("NonAssetData/kernels"),
		bool ErrorIfNoFilesFound = true,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	/**
	 * Furnish a program with SPICE kernels
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/furnsh_c.html
	 */
	SPICE_API bool Furnsh(
		const FString& relativePath = TEXT("NonAssetData/kernels/naif0012.tls"),
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	/**
	 * Furnish a program with SPICE kernels
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/furnsh_c.html
	 */
	SPICE_API bool Furnsh(
		const TArray<FString>& relativePaths,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	SPICE_API bool Unload(
		const FString& relativePath,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	SPICE_API FSEphemerisTime Now();

	/**
	 * Fetch from the kernel pool the double precision values of an item associated with a body.
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html
	 */
	SPICE_API void Bodvrd(
		double& Value,
		const FString& bodynm,
		const FString& item,
		ES_ResultCode* ResultCode,
		FString* ErrorMessage
	);

	/**
	 * Fetch from the kernel pool the double precision values of an item associated with a body.
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html
	 */
	template<typename ValueType>
	SPICE_API void Bodvrd(
		ValueType& Value,
		const FString& bodynm,
		const FString& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	/**
	 * Fetch from the kernel pool the double precision values of an item associated with a body.
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html
	 */
	template<typename ValueType>
	inline void Bodvrd(
		ValueType& Value,
		const FName& bodynm,
		const FName& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		Bodvrd<ValueType>(Value, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
	}

	// Note that an ANSICHAR version could avoid a bunch of string conversions, but that's an optimization to use only if a
	// proven problem exists.  The performance of Bodvrd is likely to be dominated by whatever's going on in bodvrd_c, not
	// string conversions.
	template<typename ValueType>
	inline void Bodvrd(
		ValueType& Value,
		const TCHAR* bodynm,
		const TCHAR* item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr)
	{
		Bodvrd<ValueType>(Value, FString(bodynm), FString(item), ResultCode, ErrorMessage);
	}

	template<typename ValueType>
	inline ValueType Bodvrd(
		const FString& bodynm,
		const FString& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		ValueType ReturnValue;
		Bodvrd<ValueType>(ReturnValue, bodynm, item, ResultCode, ErrorMessage);
		return ReturnValue;
	}

	template<>
	inline double Bodvrd(
		const FString& bodynm,
		const FString& item,
		ES_ResultCode* ResultCode,
		FString* ErrorMessage
	)
	{
		double ReturnValue;
		Bodvrd(ReturnValue, bodynm, item, ResultCode, ErrorMessage);
		return ReturnValue;
	}

	template<typename ValueType>
	inline ValueType Bodvrd(
		const FName& bodynm,
		const FName& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		return Bodvrd<ValueType>(bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
	}

	// TCHAR prevents an ambiguous definition whenever the user uses them, since both
	// FString and FName could resolve from TCHAR*
	template<typename ValueType>
	inline ValueType Bodvrd(
		const TCHAR* bodynm,
		const TCHAR* item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr)
	{
		return Bodvrd<ValueType>(FString(bodynm), FString(item), ResultCode, ErrorMessage);
	}

	/**
	 * Return d.p. values from the kernel pool
	 * (Body Value Code Double)
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvcd_c.html
	 */
	SPICE_API void Bodvcd(
		double& Value,
		int bodyid,
		const FString& item,
		ES_ResultCode* ResultCode,
		FString* ErrorMessage
	);

	template<typename ValueType>
	SPICE_API void Bodvcd(
		ValueType& Value,
		int bodyid = 399,
		const FString& item = TEXT("RADII"),
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	template<typename ValueType>
	inline void Bodvcd(
		ValueType& Value,
		int bodyid = 399,
		const FName& item = TEXT("RADII"),
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		Bodvcd<ValueType>(Value, bodyid, item.ToString(), ResultCode, ErrorMessage);
	}

	template<typename ValueType>
	inline ValueType Bodvcd(
		int bodyid = 399,
		const FString& item = TEXT("RADII"),
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		ValueType ReturnValue;
		Bodvcd<ValueType>(ReturnValue, bodyid, item, ResultCode, ErrorMessage);
		return ReturnValue;
	}

	template<>
	inline double Bodvcd(
		int bodyid,
		const FString& item,
		ES_ResultCode* ResultCode,
		FString* ErrorMessage
	)
	{
		double ReturnValue;
		Bodvcd(ReturnValue, bodyid, item, ResultCode, ErrorMessage);
		return ReturnValue;
	}

	template<typename ValueType>
	inline ValueType Bodvcd(
		int bodyid = 399,
		const FName& item = "RADII",
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		return Bodvcd<ValueType>(bodyid, item.ToString(), ResultCode, ErrorMessage);
	}

	/**
	 * Get d.p. values from the kernel pool
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/gdpool_c.html
	 */
	SPICE_API void Gdpool(
		double& Value,
		const FString& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	inline double Gdpool(
		const FString& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		double ReturnValue;
		Gdpool(ReturnValue, item, ResultCode, ErrorMessage);
		return ReturnValue;
	}

	// Gdpool
	// Only support FStrings, at least for now...
	template<typename ValueType>
	SPICE_API void Gdpool(
		ValueType& Value,
		const FString& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	);

	template<typename ValueType>
	inline ValueType Gdpool(
		const FString& item,
		ES_ResultCode* ResultCode = nullptr,
		FString* ErrorMessage = nullptr
	)
	{
		ValueType ReturnValue;
		Gdpool<ValueType>(ReturnValue, item, ResultCode, ErrorMessage);
		return ReturnValue;
	}

	// Name / ID code mappins
	/**
	 * Body string to ID code translation
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bods2c_c.html
	 */
	SPICE_API bool Bods2c(
		int& code,
		const FString& name = TEXT("EARTH")
	);
	inline bool Bods2c(int& code, FName name) { return Bods2c(code, name.ToString());}
	inline bool Bods2c(int& code, TCHAR* name) { return Bods2c(code, FString(name));}

	/**
	 * Body ID code to name translation
	 * https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodc2n_c.html
	 */
	SPICE_API bool Bodc2n(
		FString& name,
		int code = 399
	);
	inline bool Bodc2n(FName& name, int code = 399)
	{
		FString _name;
		bool result = Bodc2n(_name, code);
		name = FName(_name);
		return result;
	}

	SPICE_API bool Bodfnd(
		int body,
		const FString& item
	);
	inline bool Bodfnd(int body, FName item) { return Bodfnd(body, item.ToString()); }
	inline bool Bodfnd(int body, TCHAR* item) { return Bodfnd(body, FString(item)); }


	SPICE_API void Boddef(
		const FString& name,
		int code = 3788040
	);
	inline void Boddef(FName name = "OUMUAMUA", int code = 3788040) { return Boddef(name.ToString(), code); }
	inline void Boddef(TCHAR* name, int code = 3788040) { return Boddef(FString(name), code); }
};
