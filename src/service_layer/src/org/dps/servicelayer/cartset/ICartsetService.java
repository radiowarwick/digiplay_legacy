package org.dps.servicelayer.cartset;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

import org.dps.servicelayer.cartset.wrappers.CartsetRequest;
import org.dps.servicelayer.cartset.wrappers.CartsetResponse;

@WebService(targetNamespace = "http://www.dps.org/dps/cartset", name = "CartsetService")
@SOAPBinding(parameterStyle = SOAPBinding.ParameterStyle.BARE, style = Style.DOCUMENT)
public interface ICartsetService {
	
	@WebResult(partName = "response")
    @WebMethod()
   public CartsetResponse getCartset(
		   @WebParam(partName = "parameters")
		   CartsetRequest params);
	
}
