/*
* This file is part of Wakanda software, licensed by 4D under
*  (i) the GNU General Public License version 3 (GNU GPL v3), or
*  (ii) the Affero General Public License version 3 (AGPL v3) or
*  (iii) a commercial license.
* This file remains the exclusive property of 4D and/or its licensors
* and is protected by national and international legislations.
* In any event, Licensee's compliance with the terms and conditions
* of the applicable license constitutes a prerequisite to any use of this file.
* Except as otherwise expressly stated in the applicable license,
* such license does not include any other license or rights on this file,
* 4D's and/or its licensors' trademarks and/or other proprietary rights.
* Consequently, no title, copyright or other proprietary rights
* other than those specified in the applicable license is granted.
*/
#ifndef __HTTP_MESSAGE_INCLUDED__
#define __HTTP_MESSAGE_INCLUDED__

class VHTTPHeader;


class VHTTPMessage : public XBOX::VObject
{
public:
								VHTTPMessage();
	virtual						~VHTTPMessage();

	void						Clear();

	bool						GetDisposeBody () const  { return fDisposeBody; }
	void						SetDisposeBody (bool inValue) { fDisposeBody = inValue; }

	XBOX::VPtrStream&			GetBody();
	const XBOX::VPtrStream&		GetBody() const;

	VHTTPHeader&				GetHeaders() { return fHeaders; }
	const VHTTPHeader&			GetHeaders() const { return fHeaders; }

	enum HTTPParsingState
	{
		PS_Undefined,
		PS_ReadingRequestLine,
		PS_ReadingHeaders,
		PS_ReadingBody,
		PS_ParsingFinished
	};

	XBOX::VError				ReadFromStream (XBOX::VStream& inStream, const XBOX::VString& inBoundary);

protected:
	XBOX::VError				_ReadFromStream (	XBOX::VStream& inStream,
													const XBOX::VString& inBoundary,
													XBOX::VString *outRequestLine,
													HTTPRequestMethod *outRequestMethod,
													HTTPVersion *outRequestHTTPVersion,
													XBOX::VString *outHost,
													XBOX::VString *outRawURL,
													XBOX::VString *outURL,
													XBOX::VString *outURLPath,
													XBOX::VString *outURLQuery,
													HTTPParsingState *outParsingState,
													XBOX::VError *outParsingError);

private:
	VHTTPHeader					fHeaders;
	mutable XBOX::VPtrStream *	fBody;
	bool						fDisposeBody;	// Do NOT systematically dispose body (data can be owned by cache manager)
};


#endif // __HTTP_MESSAGE_INCLUDED__


