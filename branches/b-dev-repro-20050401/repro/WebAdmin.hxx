#if !defined(RESIP_WEBADMIN_HXX)
#define RESIP_WEBADMIN_HXX 

#include "resiprocate/os/Data.hxx"
#include "resiprocate/os/Socket.hxx"
#include "resiprocate/os/TransportType.hxx"
#include "resiprocate/os/Tuple.hxx"

namespace repro
{
class HttpConnection;

class HttpBase
{
      friend class HttpConnection;
      
   public:
      HttpBase( int port, resip::IpVersion version);
      virtual ~HttpBase();
      
      void buildFdSet(resip::FdSet& fdset);
      void process(resip::FdSet& fdset);

   protected:
      virtual void buildPage( const resip::Data& uri, int pageNumber )=0;
      void setPage( const resip::Data& page, int pageNumber );
      
   private:
      static const int MaxConnections = 10;
      
      resip::Socket mFd;
      int nextConnection;
      resip::Tuple mTuple;

      HttpConnection* mConnection[MaxConnections];
};


class HttpConnection
{
      friend class HttpBase;
      
   public:
      HttpConnection( HttpBase& webAdmin, resip::Socket pSock );
      ~HttpConnection();
      
      void buildFdSet(resip::FdSet& fdset);
      bool process(resip::FdSet& fdset);

      void setPage(const resip::Data& page);

   private:
      bool processSomeReads();
      bool processSomeWrites();
      void tryParse();
            
      HttpBase& mHttpBase;
      const int mPageNumber;
      static int nextPageNumber;
            
      resip::Socket mSock;
      resip::Data mRxBuffer;
      resip::Data mTxBuffer;
      bool mParsedRequest;
};


class WebAdmin: public HttpBase
{
   public:
      WebAdmin( int port, resip::IpVersion version=resip::V4);
      
   protected:
      virtual void buildPage( const resip::Data& uri, int pageNumber );

   private: 
      resip::Data buildUserPage();
};



}

#endif  

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
