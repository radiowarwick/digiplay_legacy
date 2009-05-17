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
	
//
// Cartset functions
//
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
	
//
// Cartwall functions
//
	@WebResult(name = "addCartwall", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public AddCartwallResponse addCartwall(
    		@WebParam(partName = "parameters", name = "addCartwallRequest", targetNamespace = Namespaces.CARTSET)
		   AddCartwallRequest params);
	
//
// CartAudio functions
//
	@WebResult(name = "addCart", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public AddCartResponse addCart(
    		@WebParam(partName = "parameters", name = "addCartRequest", targetNamespace = Namespaces.CARTSET)
		   AddCartRequest params);
	
	
//
// CartStyle functions
//
	@WebResult(name = "getCartStyles", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public GetCartStylesResponse getCartStyles(
    		@WebParam(partName = "parameters", name = "getCartStylesRequest", targetNamespace = Namespaces.CARTSET)
		   GetCartStylesRequest params);
	
	@WebResult(name = "getCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public GetCartStyleResponse getCartStyle(
    		@WebParam(partName = "parameters", name = "getCartStyleRequest", targetNamespace = Namespaces.CARTSET)
		   GetCartStyleRequest params);
	
	@WebResult(name = "addCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public AddCartStyleResponse addCartStyle(
    		@WebParam(partName = "parameters", name = "addCartStyleRequest", targetNamespace = Namespaces.CARTSET)
		   AddCartStyleRequest params);
	
	@WebResult(name = "updateCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public UpdateCartStyleResponse updateCartStyle(
    		@WebParam(partName = "parameters", name = "updateCartStyleRequest", targetNamespace = Namespaces.CARTSET)
		   UpdateCartStyleRequest params);
	
	@WebResult(name = "deleteCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public DeleteCartStyleResponse deleteCartStyle(
    		@WebParam(partName = "parameters", name = "deleteCartStyleRequest", targetNamespace = Namespaces.CARTSET)
		   DeleteCartStyleRequest params);
	
	@WebResult(name = "addCartStyleProperty", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public AddCartStylePropertyResponse addCartStyleProperty(
    		@WebParam(partName = "parameters", name = "addCartStylePropertyRequest", targetNamespace = Namespaces.CARTSET)
		   AddCartStylePropertyRequest params);
	
	@WebResult(name = "deleteCartStyleProperty", targetNamespace = Namespaces.CARTSET, partName = "response")
    @WebMethod
    public DeleteCartStylePropertyResponse deleteCartStyleProperty(
    		@WebParam(partName = "parameters", name = "deleteCartStylePropertyRequest", targetNamespace = Namespaces.CARTSET)
		   DeleteCartStylePropertyRequest params);
}
