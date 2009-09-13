package org.dps.servicelayer.cartset;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.ParameterStyle;

import org.codehaus.jra.Delete;
import org.codehaus.jra.Get;
import org.codehaus.jra.HttpResource;
import org.codehaus.jra.Post;
import org.codehaus.jra.Put;
import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.common.PermissionFault;
import org.dps.servicelayer.dto.Cartset;

/**
 * @author Phil
 *
 */
@WebService(targetNamespace = Namespaces.CARTSET)
@SOAPBinding(parameterStyle = ParameterStyle.BARE)
public interface ICartsetService {
	
//
// Cartset functions
//
	
	/**
	 * Returns a list of all permissioned cartsets.
	 * @param request_ Optional request parameters.
	 * @return a list of cartsets.
	 */
	@Get
    @HttpResource(location = "/cartsets", queryParameters = "resultsPerPage={resultsPerPage}")
	//@WebResult(name = "Cartsets")
	public Cartsets getCartsets(
			@WebParam(name = "Request", targetNamespace = Namespaces.CARTSET)
			CartsetsRequest request_);
	
    /**
     * Returns all of the details of a cartset.
     * @param request_ Request parameters.
     * @return The cartset requested.
     * @throws CartsetNotFoundFault Unable to find required cartset.
     * @throws PermissionFault Not permissioned for requested resource.
     */
    @Get
    @HttpResource(location = "/cartsets/{cartsetID}")
    public Cartset getCartset(
    		@WebParam(name = "GetCartset", targetNamespace = Namespaces.CARTSET)
		   CartsetRequest request_) throws CartsetNotFoundFault, PermissionFault;

    
	/**
	 * Update the details of a cartset.
	 * @param cartset_ The cartset to update.
	 * @throws CartsetNotFoundFault Unable to find required cartset.
     * @throws PermissionFault Not permissioned for requested resource.
	 */
	@Put
    @HttpResource(location = "/cartsets/{id}")
    public void updateCartset(
    	   @WebParam(name = "Cartset", targetNamespace = Namespaces.CARTSET)
 		   Cartset cartset_) throws CartsetNotFoundFault, PermissionFault;
	
	/**
	 * Add a new cartset.
	 * @param cartset The cartset to add.
	 * @return The ID of the new cartset.
	 * @throws PermissionFault Not permissioned for the requested action.
	 */
	@Post
    @HttpResource(location = "/cartsets")
    public Long addCartset(
    		@WebParam(name = "Cartset", targetNamespace = Namespaces.CARTSET)
		   Cartset cartset) throws PermissionFault;
	
	/**
	 * Delete the requested cartset
	 * request_ Request parameters.
	 * @throws CartsetNotFoundFault Unable to find required cartset.
     * @throws PermissionFault Not permissioned for requested resource.
	 */
	@Delete
    @HttpResource(location = "/cartsets/{id}")
    public void deleteCartset(
    		@WebParam(name = "id", targetNamespace = Namespaces.CARTSET)
		   CartsetRequest id) throws CartsetNotFoundFault, PermissionFault;
//	
////
//// Cartwall functions
////
//	@WebResult(name = "addCartwall", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public AddCartwallResponse addCartwall(
//    		@WebParam(partName = "parameters", name = "addCartwallRequest", targetNamespace = Namespaces.CARTSET)
//		   AddCartwallRequest params);
//	
////
//// CartAudio functions
////
//	@WebResult(name = "addCart", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public AddCartResponse addCart(
//    		@WebParam(partName = "parameters", name = "addCartRequest", targetNamespace = Namespaces.CARTSET)
//		   AddCartRequest params);
//	
//	
////
//// CartStyle functions
////
//	@WebResult(name = "getCartStyles", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public GetCartStylesResponse getCartStyles(
//    		@WebParam(partName = "parameters", name = "getCartStylesRequest", targetNamespace = Namespaces.CARTSET)
//		   GetCartStylesRequest params);
//	
//	@WebResult(name = "getCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public GetCartStyleResponse getCartStyle(
//    		@WebParam(partName = "parameters", name = "getCartStyleRequest", targetNamespace = Namespaces.CARTSET)
//		   GetCartStyleRequest params);
//	
//	@WebResult(name = "addCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public AddCartStyleResponse addCartStyle(
//    		@WebParam(partName = "parameters", name = "addCartStyleRequest", targetNamespace = Namespaces.CARTSET)
//		   AddCartStyleRequest params);
//	
//	@WebResult(name = "updateCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public UpdateCartStyleResponse updateCartStyle(
//    		@WebParam(partName = "parameters", name = "updateCartStyleRequest", targetNamespace = Namespaces.CARTSET)
//		   UpdateCartStyleRequest params);
//	
//	@WebResult(name = "deleteCartStyle", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public DeleteCartStyleResponse deleteCartStyle(
//    		@WebParam(partName = "parameters", name = "deleteCartStyleRequest", targetNamespace = Namespaces.CARTSET)
//		   DeleteCartStyleRequest params);
//	
//	@WebResult(name = "addCartStyleProperty", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public AddCartStylePropertyResponse addCartStyleProperty(
//    		@WebParam(partName = "parameters", name = "addCartStylePropertyRequest", targetNamespace = Namespaces.CARTSET)
//		   AddCartStylePropertyRequest params);
//	
//	@WebResult(name = "deleteCartStyleProperty", targetNamespace = Namespaces.CARTSET, partName = "response")
//    @WebMethod
//    public DeleteCartStylePropertyResponse deleteCartStyleProperty(
//    		@WebParam(partName = "parameters", name = "deleteCartStylePropertyRequest", targetNamespace = Namespaces.CARTSET)
//		   DeleteCartStylePropertyRequest params);
}
