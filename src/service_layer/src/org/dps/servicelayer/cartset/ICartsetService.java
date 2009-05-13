package org.dps.servicelayer.cartset;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;

import org.dps.servicelayer.Namespaces;

@WebService(targetNamespace = Namespaces.CARTSET, name = "CartsetService")
@SOAPBinding(parameterStyle = SOAPBinding.ParameterStyle.BARE)
public interface ICartsetService {
	
	@WebResult(name = "getCartset", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public CartsetResponse getCartset(
    		@WebParam(partName = "parameters", name = "cartsetRequest", targetNamespace = Namespaces.CARTSET)
		   CartsetRequest params);
	
	@WebResult(name = "getCartsets", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public CartsetsResponse getCartsets(
    		@WebParam(partName = "parameters", name = "cartsetsRequest", targetNamespace = Namespaces.CARTSET)
		   CartsetsRequest params);
	
	@WebResult(name = "addCartset", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public AddCartsetResponse addCartset(
    		@WebParam(partName = "parameters", name = "addCartsetRequest", targetNamespace = Namespaces.CARTSET)
		   AddCartsetRequest params);
	
	@WebResult(name = "addCartwall", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public AddCartwallResponse addCartwall(
    		@WebParam(partName = "parameters", name = "addCartwallRequest", targetNamespace = Namespaces.CARTSET)
		   AddCartwallRequest params);
}
